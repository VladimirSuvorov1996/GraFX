#pragma once
#include "Constants.hxx"
#include "WindowBased.hxx"
namespace graFX::window {
	class EventDispatcher : protected details::WindowBased {
	public:
		EventDispatcher(window_handle_ref_t base) : WindowBased(base) {}
		//You shold call this method before an input checking
		//(before you call is_key_|is_mouse_button_pressed )
		static void poll_events() {
			glfwPollEvents();
		}

		static void wait_events() {
			glfwWaitEvents();
		}
		using seconds = double;
		static bool set_wait_events_timeout(seconds timeout) {			
			if (timeout > 0) {
				glfwWaitEventsTimeout(timeout);
				return true;
			}
			return false;
		}

		static void post_empty_event() {
			glfwPostEmptyEvent();
		}

		using on_move_cb = callbacks::on_move_cb;
		using on_resize_cb = callbacks::on_resize_cb;
		using on_close_cb = callbacks::on_close_cb;
		using on_refresh_cb = callbacks::on_refresh_cb;
		using on_focus_cb = callbacks::on_focus_cb;
		using on_iconify_cb = callbacks::on_iconify_cb;
		using on_maximize_cb = callbacks::on_maximize_cb;


		using on_framebuffer_resized_cb = callbacks::on_framebuffer_resized_cb;
		using on_content_scaled_cb = callbacks::on_content_scaled_cb;

		using on_file_s_dropped_cb = callbacks::on_file_s_dropped_cb;



		//TODO: Substitute following with listeners *observers*

		on_move_cb on_move(on_move_cb callback) {
			return invoke_get<glfwSetWindowPosCallback, on_move_cb>(nullptr, window_handle_, callback);
		}
		on_resize_cb on_resize(on_resize_cb callback) {
			return invoke_get<glfwSetWindowSizeCallback, on_resize_cb>(nullptr, window_handle_, callback);
		}
		on_close_cb on_close(on_close_cb callback) {
			return invoke_get<glfwSetWindowCloseCallback, on_close_cb>(nullptr, window_handle_, callback);
		}
		on_refresh_cb on_refresh(on_refresh_cb callback) {
			return invoke_get<glfwSetWindowRefreshCallback, on_refresh_cb>(nullptr, window_handle_, callback);
		}
		on_focus_cb on_focus(on_focus_cb callback) {
			return invoke_get<glfwSetWindowFocusCallback, on_focus_cb>(nullptr, window_handle_, callback);
		}
		on_iconify_cb on_iconify(on_iconify_cb callback) {
			return invoke_get<glfwSetWindowIconifyCallback, on_iconify_cb>(nullptr, window_handle_, callback);
		}
		on_maximize_cb on_maximize(on_maximize_cb callback) {
			return invoke_get<glfwSetWindowMaximizeCallback, on_maximize_cb>(nullptr, window_handle_, callback);
		}
		on_framebuffer_resized_cb on_framebuffer_resized(on_framebuffer_resized_cb callback) {
			return invoke_get<glfwSetFramebufferSizeCallback, on_framebuffer_resized_cb>(nullptr, window_handle_, callback);
		}
		on_content_scaled_cb on_content_scaled(on_content_scaled_cb callback) {
			return invoke_get<glfwSetWindowContentScaleCallback, on_content_scaled_cb>(nullptr, window_handle_, callback);
		}

		on_file_s_dropped_cb on_file_s_dropped(on_file_s_dropped_cb callback) {
			return invoke_get<glfwSetDropCallback, on_file_s_dropped_cb>(nullptr, window_handle_, callback);
		}

	};
}