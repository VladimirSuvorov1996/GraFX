#pragma once
#include "Constants.hxx"
#include "WindowBased.hxx"
#include "Monitor.hxx"
namespace graFX::window {
	class Properties : protected details::WindowBased {
	public:
		using position_t = graphic_output_tvec2i;
		using size_t = graphic_output_tvec2i;
		using content_scale_t = graphic_output_tvec2f;
		struct frame { int left, top, right, bottom; };
		using window_area_t = graphic_output_trect2i;

		Properties(window_handle_ref_t base) : WindowBased(base) {}

		void title(const char* title) {
			invoke_set<glfwSetWindowTitle>(window_handle_, title);	
		}

		void clipboard_string(const char* the_clipboard_string) {
			invoke_set<glfwSetClipboardString>(window_handle_, the_clipboard_string);	
		}
		const char* clipboard_string()const {
			return invoke_get<glfwGetClipboardString, const char*>(nullptr, window_handle_);
		}

		void position(int x, int y) {
			invoke_set<glfwSetWindowPos>(window_handle_, x, y);	
		}
		position_t position()const {
			int x=0, y=0;
			invoke_set<glfwGetWindowPos>(window_handle_, &x, &y);	
			return { x,y };
		}

		void size(int w, int h) {
			invoke_set<glfwSetWindowSize>(window_handle_, w, h);			
		}
		size_t size()const {
			int w=0, h=0;
			invoke_set<glfwGetWindowSize>(window_handle_, &w, &h);
			return { w,h };
		}


		void set_size_limits(size_t min, size_t max) {
			invoke_set<glfwSetWindowSizeLimits>(window_handle_, min.w, min.h, max.w, max.h);
		}

		void set_aspect_ratio(int numerator, int denominator) {
			invoke_set<glfwSetWindowAspectRatio>(window_handle_, numerator, denominator);
		}


		size_t frame_buffer_size()const {
			int w=0, h=0;
			invoke_set<glfwGetFramebufferSize>(window_handle_, &w, &h);
			return{ w,h };
		}
		frame frame_size()const {
			int l=0, t=0, r=0, b=0;
			invoke_set<glfwGetWindowFrameSize>(window_handle_, &l, &t, &r, &b);
			return { l,t,r,b };
		}

		bool visible(bool is_visible) {
			if (!is_valid())return false;
			(is_visible) ? glfwShowWindow(window_handle_) : glfwHideWindow(window_handle_);
			return is_visible;
		}
		
		content_scale_t content_scale()const {
			content_scale_t content_scale ={ 0,0 };
			invoke_set<glfwGetWindowContentScale>(window_handle_, &content_scale.x, &content_scale.y);
			return content_scale;
		}

		void opacity(float v) {
			invoke_set<glfwSetWindowOpacity>(window_handle_, v);
		}
		float opacity()const {
			return invoke_get<glfwGetWindowOpacity>(0.f, window_handle_);
		}

		Monitor monitor()const {
			return Monitor::make(invoke_get<glfwGetWindowMonitor, Monitor::monitor_handle_t>(nullptr, window_handle_));
		}
		Monitor monitor(Monitor monitor, window_area_t window_area, int refreshRate) {
			invoke_set<glfwSetWindowMonitor>(window_handle_, monitor.monitor_handle_, window_area.x, window_area.y,window_area.w, window_area.h, refreshRate);
			return monitor;
		}

		CreationParameter get_parameter(CreationParameter parameter)const {
			parameter = invoke_get<glfwGetWindowAttrib, int>(0, window_handle_, parameter.hint());
			return parameter;
		}
		void set_parameter(CreationParameter parameter)const {
			invoke_set<glfwSetWindowAttrib>(window_handle_, parameter.hint(), parameter.value());
		}


		//just a flag, useful to check
		bool should_close() const {
			return invoke_get<glfwWindowShouldClose, bool>(true, window_handle_);
		}

		bool should_close(bool should_close) {
			invoke_set<glfwSetWindowShouldClose>(window_handle_, should_close);
			return should_close;
		}

		using user_data_pointer_t = void*;
		void set_user_pointer(user_data_pointer_t user_data) {
			invoke_set<glfwSetWindowUserPointer>(window_handle_, user_data);
		}

		user_data_pointer_t get_user_pointer() {
			return invoke_get<glfwGetWindowUserPointer, user_data_pointer_t>(nullptr, window_handle_);
		}
	};
}