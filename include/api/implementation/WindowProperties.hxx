#pragma once
#include "Constants.hxx"
#include "WindowBased.hxx"
namespace graFX::window {
	class Properties : protected details::WindowBased {
	public:
		using position_t = graphic_output_tvec2i;
		using size_t = graphic_output_tvec2i;
		struct frame { int left, top, right, bottom; };

		Properties(window_handle_ref_t base) : WindowBased(base) {}

		void title(const char* title) {
			if (is_valid())glfwSetWindowTitle(window_handle_, title);
		}

		void clipboard_string(const char* the_clipboard_string) {
			if (is_valid())glfwSetClipboardString(window_handle_, the_clipboard_string);
		}
		const char* clipboard_string()const {
			return (is_valid()) ? glfwGetClipboardString(window_handle_) : nullptr;
		}

		void position(int x, int y) {
			if (is_valid())glfwSetWindowPos(window_handle_, x, y);
		}
		position_t position()const {
			if (!is_valid())return{ 0,0 };
			int x, y;
			glfwGetWindowPos(window_handle_, &x, &y);
			return { x,y };
		}

		void size(int w, int h) {
			if (is_valid())glfwSetWindowSize(window_handle_, w, h);
		}
		size_t size()const {
			if (!is_valid())return{ 0,0 };
			int w, h;
			glfwGetWindowSize(window_handle_, &w, &h);
			return { w,h };
		}


		void set_size_limits(size_t min, size_t max) {
			if (is_valid())glfwSetWindowSizeLimits(window_handle_, min.w, min.h, max.w, max.h);
		}

		void set_aspect_ratio(int numerator, int denominator) {
			if (is_valid())glfwSetWindowAspectRatio(window_handle_, numerator, denominator);
		}


		size_t frame_buffer_size()const {
			if (!is_valid())return{ 0,0 };
			int w, h;
			glfwGetFramebufferSize(window_handle_, &w, &h);
			return{ w,h };
		}
		frame frame_size()const {
			if (!is_valid())return{ 0,0,0,0 };
			int l, t, r, b;
			glfwGetWindowFrameSize(window_handle_, &l, &t, &r, &b);
			return { l,t,r,b };
		}

		bool visible(bool is_visible) {
			if (!is_valid())return false;
			(is_visible) ? glfwShowWindow(window_handle_) : glfwHideWindow(window_handle_);
			return is_visible;
		}

		//just a flag, useful to check
		bool should_close() const {
			return (is_valid()) ? glfwWindowShouldClose(window_handle_) : true;
		}

		bool should_close(bool should_close) {
			if (is_valid())glfwSetWindowShouldClose(window_handle_, should_close);
			return should_close;
		}
	};
}