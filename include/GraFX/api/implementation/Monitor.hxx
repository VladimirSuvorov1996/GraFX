#pragma once
#include <gsl-lite.hpp>
#include "GraFX.hxx"
#include "Constants.hxx"
#include "GraFX/api/basic_observers/basic/ObserverCore.hpp"
#include "CallbackSignatures.hxx"
#include "ScopedHandle.hxx"

namespace graFX {
	class Window;
	namespace window {
		class Properties;
	}
}



namespace graFX {	
	class Monitor;
	class AvailableVideoModes;

	struct videomode_traits {
		using videomode_t = const GLFWvidmode*;

		static int get_width(videomode_t videomode)noexcept { return videomode->width; }
		static int get_height(videomode_t videomode)noexcept { return videomode->height; }
		static int get_redBits(videomode_t videomode)noexcept { return videomode->redBits; }
		static int get_greenBits(videomode_t videomode)noexcept { return videomode->greenBits; }
		static int get_blueBits(videomode_t videomode)noexcept { return videomode->blueBits; }
		static int get_refreshRate(videomode_t videomode)noexcept { return videomode->refreshRate; }
	};

	class CurrentVideoMode {		//current videomode
	protected:		
	public:
		CurrentVideoMode(CurrentVideoMode&& src) :
			monitor_(src.monitor_)
		{}
		int width		()const noexcept { return invoke_get<videomode_traits::get_width,		0>(); }
		int height		()const noexcept { return invoke_get<videomode_traits::get_height,		0>(); }
		int redBits		()const noexcept { return invoke_get<videomode_traits::get_redBits,		0>(); }
		int greenBits	()const noexcept { return invoke_get<videomode_traits::get_greenBits,	0>(); }
		int blueBits	()const noexcept { return invoke_get<videomode_traits::get_blueBits,	0>(); }
		int refreshRate	()const noexcept { return invoke_get<videomode_traits::get_refreshRate,	0>(); }
	protected:

		template<auto callable, int defaultValue>
		int invoke_get()const noexcept {
			videomode_traits::videomode_t mode = videomode();
			return (mode)? callable(mode) : defaultValue;
		}	

		videomode_traits::videomode_t videomode()const noexcept; 
		CurrentVideoMode(const Monitor& monitor) :
			monitor_(monitor)
		{}
	protected:
		const Monitor& monitor_;
	protected:
		friend class Monitor;
		friend class AvailableVideoModes;
	};
	
	class AvailableVideoModes {		
	protected:		
		using available_videomodes_t = gsl::span<const GLFWvidmode>;
	public:
		AvailableVideoModes(AvailableVideoModes&& src) :
			monitor_(src.monitor_)
		{}
		class video_mode {
		public:
			video_mode(size_t mode_index, const AvailableVideoModes& modes) :
				mode_index_(mode_index),
				modes_(modes) 
			{}
			video_mode(const video_mode& oth) :
				mode_index_(oth.mode_index_),
				modes_(oth.modes_) 
			{}
			video_mode(video_mode&& src) :
				mode_index_(src.mode_index_),				
				modes_(src.modes_)
			{}
			
			int width		()const noexcept { 
				return modes_.mode_width(mode_index_);
			}
			int height		()const noexcept { 
				return modes_.mode_height(mode_index_);
			}
			int redBits		()const noexcept { 
				return modes_.mode_redBits(mode_index_);
			}
			int greenBits	()const noexcept { 
				return modes_.mode_greenBits(mode_index_);
			}
			int blueBits	()const noexcept {
				return modes_.mode_blueBits(mode_index_); 
			}
			int refreshRate()const noexcept {
				return modes_.mode_refreshRate(mode_index_);
			}
					   
		protected:
			size_t mode_index_;
			const AvailableVideoModes& modes_;
		};
		video_mode operator[](size_t mode_index)const noexcept {
			return video_mode(mode_index, *this);
		}

		int mode_width		(size_t mode_index)const noexcept { 
			return invoke_get<videomode_traits::get_width,		0>(mode_index); 
		}
		int mode_height		(size_t mode_index)const noexcept { 
			return invoke_get<videomode_traits::get_height,		0>(mode_index); 
		}
		int mode_redBits	(size_t mode_index)const noexcept { 
			return invoke_get<videomode_traits::get_redBits,	0>(mode_index); 
		}
		int mode_greenBits	(size_t mode_index)const noexcept { 
			return invoke_get<videomode_traits::get_greenBits,	0>(mode_index); 
		}
		int mode_blueBits	(size_t mode_index)const noexcept { 
			return invoke_get<videomode_traits::get_blueBits,	0>(mode_index); 
		}
		int mode_refreshRate(size_t mode_index)const noexcept {
			return invoke_get<videomode_traits::get_refreshRate,0>(mode_index); 
		}
		size_t size()const noexcept {
			return  available_videomodes().size();
		}
	protected:
		template<auto callable, int defaultValue>
		int invoke_get(size_t index)const noexcept {
			available_videomodes_t modes = available_videomodes();
			return (index<modes.size())? callable(&modes[index]) : defaultValue;
		}	

		available_videomodes_t available_videomodes()const noexcept; 
		AvailableVideoModes(const Monitor& monitor) :
			monitor_(monitor)
		{}
	protected:
		const Monitor& monitor_;
	protected:
		friend class Monitor;
	};
	
	class GammaRamp {
	protected:
		using gamma_ramp_pointer = GLFWgammaramp *;
		using const_gamma_ramp_pointer = const GLFWgammaramp *;

		using gamma_ramp_value = decltype(std::declval<gamma_ramp_pointer>()->red);		
		using const_gamma_ramp_value = decltype(std::declval<const_gamma_ramp_pointer>()->red);		
		
		using gamma_ramp_values = gsl::span<std::remove_pointer_t<gamma_ramp_value>>;
		using const_gamma_ramp_values = gsl::span<std::remove_pointer_t<const_gamma_ramp_value>>;

	public:	
		GammaRamp() :
			monitor_(nullptr),
			size_(0)
		{}
		GammaRamp(GammaRamp&& src) :
			monitor_(src.monitor_),
			size_(src.size_)
		{}

		size_t size()const noexcept {
			if (belongs_to_monitor()) {
				const_gamma_ramp_pointer gamma = gamma_ramp();
				return size_ = (gamma)?gamma->size:0;
			}
			return size_;					 
		}
		bool size(size_t size)noexcept {
			if (belongs_to_monitor())return false;
			size_ = size;
			return true;
		}
		bool belongs_to_monitor	()const noexcept{	return monitor_;	}
		
		gamma_ramp_values red	()const noexcept{	return invoke_get<get_red,	&GammaRamp::red_	>();	}
		gamma_ramp_values green	()const noexcept{	return invoke_get<get_green,&GammaRamp::green_	>();	}
		gamma_ramp_values blue	()const noexcept{	return invoke_get<get_blue,	&GammaRamp::blue_	>();	}
		
		void reset() {
			monitor_ = nullptr;
		}
		bool red	(gamma_ramp_values values)noexcept{
			return invoke_set<&GammaRamp::red_>(values);
		}
		bool green	(gamma_ramp_values values)noexcept{
			return invoke_set<&GammaRamp::green_>(values);
		}
		bool blue	(gamma_ramp_values values)noexcept{
			return invoke_set<&GammaRamp::blue_>(values);
		}
	protected:
		template<auto setable>
		bool invoke_set(gamma_ramp_values values)noexcept {
			if (size()>values.size())return false;
			(this->*setable) = values;
			return true;
		}
		static const_gamma_ramp_value get_red(const_gamma_ramp_pointer gamma_ramp) {
			return gamma_ramp->red;
		}
		static const_gamma_ramp_value get_green(const_gamma_ramp_pointer gamma_ramp) {
			return gamma_ramp->green;
		}
		static const_gamma_ramp_value get_blue(const_gamma_ramp_pointer gamma_ramp) {
			return gamma_ramp->blue;
		}


		template<auto callable, auto field>
		const_gamma_ramp_values invoke_get()const noexcept {
			if (!belongs_to_monitor()) return (this->*field);
			const_gamma_ramp_pointer gamma = gamma_ramp();
			if (gamma)return { callable(gamma),gamma->size };
			return { nullptr,0 };
		}

		const_gamma_ramp_pointer gamma_ramp()const noexcept;

		GammaRamp(gsl::not_null<const Monitor*> monitor) :
			monitor_(monitor),
			size_(0)
		{}
	protected:
		mutable size_t size_;
		gamma_ramp_values red_, green_, blue_;
		const Monitor* monitor_;
	protected:
		friend class Monitor;
	};

	class Monitor {
		friend class Window;
		friend class CurrentVideoMode;
		friend class AvailableVideoModes;
		friend class GammaRamp;
		friend class window::Properties;

	public:
		using monitor_handle_t = GLFWmonitor *;
		using monitor_handles_t = gsl::span<monitor_handle_t>;
		using monitor_index_t = size_t;


		using position_t = graphic_output_tvec2i;
		using physical_size_t = graphic_output_tvec2i;
		using name_t = const char*;
	
		using gamma_t = float;
		using gamma_ramp_t = GLFWgammaramp;
		using gamma_ramp_pointer = GLFWgammaramp *;
		using const_gamma_ramp_pointer = const GLFWgammaramp*;
		using work_area_t = graphic_output_trect2i;
		using content_scale_t = graphic_output_tvec2f;
	public:
		Monitor() : monitor_handle_(nullptr) {}
		Monitor(Monitor&& src) {
			create(src.monitor_handle_);
			if(src.is_connected())
				monitors_.remove(&src); 
			src.monitor_handle_ = nullptr;
		}
		/*size_t index()const noexcept {
			return index_;
		}*/
		void reset(size_t index, bool should_update = true)noexcept {
			create((index < count(should_update)) ? monitor_handles_[index] : nullptr);
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
		CurrentVideoMode current_videomode()const {
			cashed_data_.current_videomode = invoke_get<glfwGetVideoMode, videomode_t>(nullptr, monitor_handle_);
			return { *this };
		}
		
		AvailableVideoModes available_videomodes()const {
			int count = 0;
			const videomode_t videomodes = invoke_get<glfwGetVideoModes, videomode_t>(nullptr, monitor_handle_, &count);
			cashed_data_.available_videomodes = available_videomodes_t(videomodes, count);
			return { *this };
		}
		void set_gamma(gamma_t gamma) {
			invoke_set<glfwSetGamma>(monitor_handle_, gamma);
		}
		void gamma_ramp(GammaRamp gamma_ramp) {
			auto red	= gamma_ramp.red	();
			auto green	= gamma_ramp.green	();
			auto blue	= gamma_ramp.blue	();

			gamma_ramp_t	gramp ={
				red		.data(),
				green	.data(),
				blue	.data(),
				std::min({ red.size(), green.size(), blue.size() })
			};
			invoke_set<glfwSetGammaRamp>(monitor_handle_, &gramp);
		}
		GammaRamp gamma_ramp()const {
			cashed_data_.gamma_ramp = invoke_get<glfwGetGammaRamp, const_gamma_ramp_pointer>(nullptr, monitor_handle_);
			return { this };
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



		using on_monitor_connected_cb = callbacks::on_monitor_connected_cb;
		static on_monitor_connected_cb on_monitor_connected(on_monitor_connected_cb callback) {
			return glfwSetMonitorCallback(callback);
		}
		
		struct traits {
			using reference		= Monitor&;
			using pointer		= Monitor*;
			using handle_type	= GLFWmonitor *;

			static handle_type get_handle(reference data){
				return data.monitor_handle_;
			}
			static void set_handle(reference data, handle_type handle){
				data.monitor_handle_ = handle;
			}
		};
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
			using namespace std;
			return (find(cbegin(monitor_handles_), cend(monitor_handles_), monitor_handle_)==cend(monitor_handles_));
		}
	protected:
		monitor_handle_t monitor_handle_;
		
		using videomode_t = const GLFWvidmode*;
		using available_videomodes_t = gsl::span<const GLFWvidmode>; 
		videomode_t get_current_videomode()const noexcept {
			return (is_connected())?cashed_data_.current_videomode:nullptr;
		}
		available_videomodes_t get_available_videomodes()const noexcept {
			return (is_connected())?cashed_data_.available_videomodes:available_videomodes_t(nullptr, 0);
		}
		const_gamma_ramp_pointer get_gamma_ramp()const noexcept {
			return (is_connected())?cashed_data_.gamma_ramp:nullptr;
		}
	private:
		mutable struct {
			videomode_t current_videomode;
			available_videomodes_t available_videomodes;
			const_gamma_ramp_pointer gamma_ramp;
		} cashed_data_;
	protected:
		inline static graFX::input::observer_core::ObserverCore<Monitor*> monitors_;
		inline static monitor_handles_t monitor_handles_;

	
	};
	
	videomode_traits::videomode_t CurrentVideoMode::videomode()const noexcept { 
		return monitor_.get_current_videomode();
	}
	AvailableVideoModes::available_videomodes_t AvailableVideoModes::available_videomodes()const noexcept {
		return monitor_.get_available_videomodes();
	}
	
	GammaRamp::const_gamma_ramp_pointer GammaRamp::gamma_ramp()const noexcept{
		return monitor_->get_gamma_ramp();
	}

}