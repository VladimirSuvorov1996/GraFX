#pragma once
#include "Window.hxx"
#include "GraFX.hxx"
namespace input {
	using Window = graFX::Window;
}

class EventDispatcher {//for callbacks
public:
	//Monitor
	static void on_monitor_connected(/*monitor, is_connected*/) {}

	//window|area events
	static void on_window_moved(graFX::Window&, void(*callback)(graFX::Window&, int, int)/*Window, x, y*/) {}
	static void on_window_resized(/*Window, w, h*/) {}
	static void on_window_closed(/*Window*/) {}
	static void on_window_refreshed(/*Window*/) {}
	static void on_window_focused(/*Window, is_focused*/) {}
	static void on_window_iconified(/*Window, is_iconified*/) {}
	static void on_window_framebuffer_resized(/*Window, w, h*/) {}

	//input events
	//Mouse
	static void on_mouse_button(/*Window, button, is_pressed, modifiers*/) {}
	static void on_mouse_moved(/*Window, x, y*/) {} //(left, top)
	static void on_mouse_entered(/*Window, is_entered*/) {}
	static void on_mouse_scrolled(/*Window, ox, oy*/) {}

	//Keyboard
	static void on_key(/*Window, key, specific_code, action, modifiers*/) {}
	static void on_char_entered(/*Window, utf-char*/) {}
	static void on_modified_char_entered(/*Window, utf-char, modifiers*/) {}

	//Joystic
	static void on_joystic_connected(/*joystic_id, is_connected*/) {}

	//File
	static void on_file_s_dropped(/*Window, file_s_count, path_es*/) {}



	

};