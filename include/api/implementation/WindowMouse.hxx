#pragma once
#include "Button.hxx"
#include "WindowBased.hxx"
namespace graFX::window {
	class Mouse : protected details::WindowBased {
	public:
		using on_cursor_moved_cb = callbacks::on_cursor_moved_cb;
		using on_cursor_enter_cb = callbacks::on_cursor_enter_cb;
		using on_scroll_cb = callbacks::on_scroll_cb;
		using on_mouse_button_cb = callbacks::on_mouse_button_cb;

		Mouse(window_handle_ref_t base) : WindowBased(base) {}
		
		enum CursorMode { Normal, Hiden, Disabled };
		//buggy two
		bool sticky_mouse_buttons()const {
			return (is_valid()) ? glfwGetInputMode(window_handle_, glfw::input_modes[StickyMouseButtons]) : false;
		}
		void sticky_mouse_buttons(bool enabled) {
			if (is_valid())glfwSetInputMode(window_handle_, glfw::input_modes[StickyMouseButtons], enabled);
		}



		CursorMode cursor_mode()const {
			return (is_valid()) ?
				static_cast<CursorMode>((glfwGetInputMode(window_handle_, glfw::input_modes[Cursor]) - glfw::cursor_modes[Normal])) :
				Normal;
		}
		void cursor_mode(CursorMode mode) {
			invoke_set<glfwSetInputMode>(window_handle_, glfw::input_modes[Cursor], glfw::cursor_modes[mode]);
		}



		void set_cursor_position(double x, double y) {
			invoke_set<glfwSetCursorPos>(window_handle_, x, y);
		}
		using position_t = graphic_output_tvec2<double>;
		position_t get_cursor_position()const {
			position_t pos ={ 0,0 };
			invoke_set<glfwGetCursorPos>(window_handle_, &pos.x, &pos.y);
			return pos;
		}
		static bool raw_mouse_motion_supported() {
			return glfwRawMouseMotionSupported();
		}

		bool is_mouse_button_pressed(Button button)const {
			return (is_valid()) ? 
				(glfwGetMouseButton(window_handle_, button.code()) == glfw::KeyPressed) :
				false;
		}

		on_cursor_moved_cb on_cursor_moved(on_cursor_moved_cb callback) {
			return invoke_get<glfwSetCursorPosCallback, on_cursor_moved_cb>(nullptr, window_handle_, callback);
		}
		on_cursor_enter_cb on_cursor_entered(on_cursor_enter_cb callback) {
			return invoke_get<glfwSetCursorEnterCallback, on_cursor_enter_cb>(nullptr, window_handle_, callback);
		}
		on_scroll_cb on_scroll(on_scroll_cb callback) {
			return invoke_get<glfwSetScrollCallback, on_scroll_cb>(nullptr, window_handle_, callback);
		}
		on_mouse_button_cb on_mouse_button(on_mouse_button_cb callback) {
			return invoke_get<glfwSetMouseButtonCallback, on_mouse_button_cb>(nullptr, window_handle_, callback);
		}
	};
}