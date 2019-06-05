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
		using on_framebuffer_resized_cb = callbacks::on_framebuffer_resized_cb;
		using on_file_s_dropped_cb = callbacks::on_file_s_dropped_cb;



		//TODO: Substitute following with listeners *observers*

		on_move_cb on_move(on_move_cb callback) {
			return (is_valid()) ? glfwSetWindowPosCallback(window_handle_, callback) : nullptr;
		}
		on_resize_cb on_resize(on_resize_cb callback) {
			return (is_valid()) ? glfwSetWindowSizeCallback(window_handle_, callback) : nullptr;
		}
		on_close_cb on_close(on_close_cb callback) {
			return (is_valid()) ? glfwSetWindowCloseCallback(window_handle_, callback) : nullptr;
		}
		on_refresh_cb on_refresh(on_refresh_cb callback) {
			return (is_valid()) ? glfwSetWindowRefreshCallback(window_handle_, callback) : nullptr;
		}
		on_focus_cb on_focus(on_focus_cb callback) {
			return (is_valid()) ? glfwSetWindowFocusCallback(window_handle_, callback) : nullptr;
		}
		on_iconify_cb on_iconify(on_iconify_cb callback) {
			return (is_valid()) ? glfwSetWindowIconifyCallback(window_handle_, callback) : nullptr;
		}
		on_framebuffer_resized_cb on_framebuffer_resized(on_framebuffer_resized_cb callback) {
			return (is_valid()) ? glfwSetFramebufferSizeCallback(window_handle_, callback) : nullptr;
		}

		on_file_s_dropped_cb on_file_s_dropped(on_file_s_dropped_cb callback) {
			return (is_valid()) ? glfwSetDropCallback(window_handle_, callback) : nullptr;
		}

	};
}