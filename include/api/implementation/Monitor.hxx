#pragma once
#include <gsl-lite.hpp>
#include "GraFX.hxx"
#include "Constants.hxx"
#include "api/basic_observers/basic/ObserverCore.hpp"
#include "CallbackSignatures.hxx"
#include "ScopedHandle.hxx"

namespace graFX {
	class Window;
	namespace window {
		class Properties;
	}
	class Monitor;

	namespace details {

		struct MonitorTraits {
			using data_reference = Monitor&;
			using handle_type = GLFWmonitor *;

			static handle_type get_handle(data_reference data); 
			static void set_handle(data_reference data, handle_type handle); 
		};
		using MonitorScopedHandle = ScopedHandle<MonitorTraits>;
	}
}
namespace graFX {
	class Monitor {
		friend class Window;
		friend class window::Properties;
		friend details::MonitorTraits;
	public:
		using monitor_handle_t = GLFWmonitor *;
		using monitor_handles_t = gsl::span<monitor_handle_t>;
		using monitor_index_t = size_t;


		using position_t = graphic_output_tvec2i;
		using physical_size_t = graphic_output_tvec2i;
		using name_t = const char*;
		using videomode_t = const GLFWvidmode*;
		using gamma_t = float;
		using gamma_ramp_t = GLFWgammaramp *;
		using const_gamma_ramp_t = const GLFWgammaramp*;
		using available_videomodes_t = gsl::span<const GLFWvidmode>;
		using work_area_t = graphic_output_trect2i;
		using content_scale_t = graphic_output_tvec2f;
	public:
		Monitor() : monitor_handle_(nullptr) {}
		Monitor(Monitor&& src) {
			create(src.monitor_handle_);
			if(src.is_connected())
				monitors_.remove(&src); 
		}
		Monitor(size_t index, bool should_update = true) {
			create((index < count(should_update)) ? monitor_handles_[index] : nullptr);
		}
		Monitor(const Monitor& oth) { create(oth.monitor_handle_); }
		~Monitor() { if(is_connected())monitors_.remove(this); }


		bool is_connected()const { return (monitor_handle_ != nullptr); }

		position_t position()const {
			position_t pos={ 0,0 };
			invoke_set<glfwGetMonitorPos>(monitor_handle_, &pos.x, &pos.y);
			return pos;
		}
		
		work_area_t get_workarea()const {
			work_area_t warea ={ 0,0,0,0 };
			invoke_set<glfwGetMonitorWorkarea>(monitor_handle_, &warea.x, &warea.y, &warea.w, &warea.h);
			return warea;
		}

		physical_size_t physical_size()const {
			physical_size_t size ={ 0,0 };
			invoke_set<glfwGetMonitorPhysicalSize>(monitor_handle_, &size.w, &size.h);
			return size;
		}
		name_t name()const {
			return invoke_get<glfwGetMonitorName, name_t>("", monitor_handle_);
		}
		videomode_t current_videomode() {
			return invoke_get<glfwGetVideoMode, videomode_t>(nullptr, monitor_handle_);
		}
		void set_gamma(gamma_t gamma) {
			invoke_set<glfwSetGamma>(monitor_handle_, gamma);
		}
		void gamma_ramp(gamma_ramp_t gamma_ramp) {
			invoke_set<glfwSetGammaRamp>(monitor_handle_, gamma_ramp);
		}
		const_gamma_ramp_t gamma_ramp()const {
			return invoke_get<glfwGetGammaRamp, const_gamma_ramp_t>(nullptr, monitor_handle_);
		}
		available_videomodes_t available_videomodes()const {
			int count = 0;
			const videomode_t videomodes = invoke_get<glfwGetVideoModes, videomode_t>(nullptr, monitor_handle_, &count);
			return available_videomodes_t(videomodes, count);
		}
		content_scale_t content_scale()const {
			content_scale_t scale ={ 0,0 };
			invoke_set<glfwGetMonitorContentScale>(monitor_handle_, &scale.x, &scale.y);
			return scale;
		}
		
		using user_data_pointer_t = void*;
		void set_user_pointer(user_data_pointer_t user_data) {
			invoke_set<glfwSetMonitorUserPointer>(monitor_handle_, user_data);
		}

		user_data_pointer_t get_user_pointer() {
			invoke_get<glfwGetMonitorUserPointer, user_data_pointer_t>(nullptr, monitor_handle_);
		}

		bool operator==(const Monitor& other)const {
			return (monitor_handle_ == other.monitor_handle_);
		}
	public:

		static Monitor& primary_monitor() {
			static Monitor primary;
			primary.monitor_handle_ = glfwGetPrimaryMonitor();
			return primary;
		}

		static size_t count(bool should_update = true) {
			if (should_update)update();
			return monitor_handles_.size();
		}

		static void update() {
			int count;//upd handles
			auto handles = glfwGetMonitors(&count);
			monitor_handles_ ={ handles, static_cast<size_t>(count) };

			//upd monitors
			for (auto monitor : monitors_)
				if (monitor->monitor_handle_)
					if (monitor->disconnected())
						monitor->monitor_handle_ = nullptr;
		}


		//TODO: substitute with listeners
		using on_monitor_connected_cb = callbacks::on_monitor_connected_cb;
		static on_monitor_connected_cb on_monitor_connected(on_monitor_connected_cb callback) {
			return glfwSetMonitorCallback(callback);
		}
		
	private:
		template<auto callable, typename R, typename...Ts>
		R invoke_get(R defaultValue, Ts&&...as)const {			
			return (is_connected())?std::invoke(callable, std::forward<Ts>(as)...):defaultValue;
		}
		template<auto callable, typename...Ts>
		void invoke_set(Ts&&...as)const {			
			if(is_connected())std::invoke(callable, std::forward<Ts>(as)...);
		}
	protected:

		
		static Monitor make(monitor_handle_t handle) {
			Monitor monitor;
			monitor.create(handle);
			return monitor;
		}

		void create(monitor_handle_t handle = nullptr) {
			monitors_.add(this);
			monitor_handle_ = handle;
		}

		bool disconnected()const {
			for (auto handle : monitor_handles_)
				if (handle == monitor_handle_)return false;
			return true;
		}
	protected:
		monitor_handle_t monitor_handle_;

	protected:
		inline static graFX::input::observer_core::ObserverCore<Monitor*> monitors_;
		inline static monitor_handles_t monitor_handles_;

	
	};



	namespace details {		
		MonitorTraits::handle_type MonitorTraits::get_handle(data_reference data) {
			return data.monitor_handle_;
		}
		void MonitorTraits::set_handle(data_reference data, handle_type handle) {
			data.monitor_handle_ = handle;
		}
		using MonitorScopedHandle_t = MonitorScopedHandle;
	}

}