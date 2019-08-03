#pragma once
#include <gsl-lite.hpp>
#include "GraFX.hxx"
#include "Constants.hxx"
#include "ObserverCore.hpp"
#include "CallbackSignatures.hxx"

namespace graFX {
	class Window;
}
namespace graFX {	
	class Monitor {
		friend class Window;
	public:
		using monitor_handle_t = GLFWmonitor * ;
		using monitor_handles_t = gsl::span<monitor_handle_t>;
		using monitor_index_t = size_t;


		using position_t = graphic_output_tvec2i;
		using physical_size_t = graphic_output_tvec2i;
		using name_t = const char*;
		using videomode_t = const GLFWvidmode*;
		using gamma_t = float;
		using gamma_ramp_t = GLFWgammaramp * ;
		using const_gamma_ramp_t = const GLFWgammaramp*;
		using available_videomodes_t = gsl::span<const GLFWvidmode>;
	public:
		Monitor(Monitor&&) = delete;
		Monitor(size_t index, bool should_update = true) {
			create((index < count(should_update)) ? monitor_handles_[index] : nullptr);
		}
		Monitor(const Monitor& oth) { create(oth.monitor_handle_); }
		~Monitor() { monitors_.remove(this); }
		
		bool is_connected()const { return (monitor_handle_ != nullptr); }
		position_t position()const {
			if (is_connected()) {
				position_t pos;
				glfwGetMonitorPos(monitor_handle_, &pos.x, &pos.y);
				return pos;
			}return{ 0,0 };
		}
		physical_size_t physical_size()const {
			if (is_connected()) {
				physical_size_t size;
				glfwGetMonitorPhysicalSize(monitor_handle_, &size.w, &size.h);
				return size;
			}return{ 0,0 };
		}
		name_t name()const {
			return (is_connected()) ? glfwGetMonitorName(monitor_handle_) : "";
		}
		videomode_t current_videomode() {
			return (is_connected()) ? glfwGetVideoMode(monitor_handle_) : nullptr;
		}
		void set_gamma(gamma_t gamma) {
			if (is_connected())glfwSetGamma(monitor_handle_, gamma);
		}
		void gamma_ramp(gamma_ramp_t gamma_ramp) {
			if (is_connected())glfwSetGammaRamp(monitor_handle_, gamma_ramp);
		}
		const_gamma_ramp_t gamma_ramp()const {
			return (is_connected()) ? glfwGetGammaRamp(monitor_handle_) : nullptr;
		}
		available_videomodes_t available_videomodes()const {
			if (is_connected()) {
				int count;
				const videomode_t videomodes = glfwGetVideoModes(monitor_handle_, &count);
				return available_videomodes_t(videomodes, count);
			}return{};
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
			monitor_handles_ = { handles, static_cast<size_t>(count) };

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

	protected:
		void create(monitor_handle_t handle = nullptr) {
			monitors_.add(this);
			monitor_handle_ = handle;
		}

		Monitor() : monitor_handle_(nullptr) {}
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
}