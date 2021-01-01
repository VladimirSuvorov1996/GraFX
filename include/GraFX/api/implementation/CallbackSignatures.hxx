#pragma once
#include "../basic_observers/basic/ObserverCore.hpp"
#include "Constants.hxx"


namespace callbacks {
	//==========================/PROCEDURES
	using glfw_procedure = void(*)();
	using vulkan_procedure = void(*)();

	//==========================/ON_ERROR
	using error_code = glfw::error_t;
	using error_text = const char*;
	using on_error_cb = void(*)(error_code, error_text);


	//==========================/ON_WINDOW_MOVED +
	using moved_window = GLFWwindow * ;
	using to_x = int;//in screen coords
	using to_y = int;
	using on_move_cb = void(*)(moved_window, to_x, to_y);


	//==========================/ON_WINDOW_RESIZED +
	using resized_window = GLFWwindow * ;
	using to_width = int;//in screen coords
	using to_height = int;
	using on_resize_cb = void(*)(resized_window, to_width, to_height);


	//==========================/ON_WINDOW_CLOSED +
	using window_to_close = GLFWwindow * ;
	using on_close_cb = void(*)(window_to_close);


	//==========================/ON_WINDOW_REFRESH +
	using window_to_refresh = GLFWwindow * ;
	using on_refresh_cb = void(*)(window_to_refresh);


	//==========================/ON_WINDOW_FOCUSED +
	using the_window_focused_on = GLFWwindow * ;
	using is_focused = int;
	using on_focus_cb = void(*)(the_window_focused_on, is_focused);


	//==========================/ON_WINDOW_ICONIFIED +
	using iconified_window = GLFWwindow * ;
	using is_iconified = int;
	using on_iconify_cb = void(*)(iconified_window, is_iconified);

	//==========================/ON_WINDOW_MAXIMIZED + 
	using maximized_window = GLFWwindow * ;
	using is_maximized = int;
	using on_maximize_cb = void(*)(maximized_window, is_maximized);


	//==========================/ON_WINDOW_FRAMEBUFFER_RESIZED +
	using window_wich_framebuffer = GLFWwindow * ;
	using to_framebuffer_width = int;
	using to_framebuffer_height = int;
	using on_framebuffer_resized_cb = void(*)(window_wich_framebuffer, to_framebuffer_width, to_framebuffer_height);

	//==========================/ON_WINDOW_CONTENT_SCALED +
	using window_wich_content_was_scaled = GLFWwindow * ;
	using to_scale_x = float;
	using to_scale_y = float;
	using on_content_scaled_cb = void(*)(window_wich_content_was_scaled, to_scale_x, to_scale_y);

	//==========================/ON_MOUSE_BUTTON input
	using window_receiver = GLFWwindow * ;
	using button = glfw::button_t;
	using is_pressed = glfw::action_t;
	using mode_bit_fields = glfw::mode_bitfields_t;//shift,ctrl,alt,super
	using on_mouse_button_cb = void(*)(window_receiver, button, is_pressed, mode_bit_fields);


	//==========================/ON_CURSOR_MOVED input
	using window_relative_to = GLFWwindow * ;
	using mouse_moved_to_x = double;//relative to: -left 
	using mouse_moved_to_y = double;//-top
	using on_cursor_moved_cb = void(*)(window_relative_to, mouse_moved_to_x, mouse_moved_to_y);


	//==========================/ON_CURSOR_ENTERED input
	using window_enter_to = GLFWwindow * ;
	using is_entered = int;
	using on_cursor_enter_cb = void(*)(window_enter_to, is_entered);


	//==========================/ON_SCROLLED input
	using window_scrolled_at = GLFWwindow * ;
	using offset_x = double;
	using offset_y = double;
	using on_scroll_cb = void(*)(window_scrolled_at, offset_x, offset_y);


	//==========================/ON_KEY input
	using window_receiver = GLFWwindow * ;
	using key = int;
	using system_specific_scancode = int;
	using action = int;//press,release,repeat
	using mode_bit_fields = glfw::mode_bitfields_t;//shift,ctrl,alt,super
	using on_key_cb = void(*)(window_receiver, key, system_specific_scancode, action, mode_bit_fields);


	//==========================/ON_CHAR_ENTERED input
	using window_receiver = GLFWwindow * ;
	using character_unicode_codepoint = unsigned int;
	using on_char_entered_cb = void(*)(window_receiver, character_unicode_codepoint);

	
	//==========================/ON_CHAR_WITH_MODS_ENTERED input
	using window_receiver = GLFWwindow * ;
	using character_unicode_codepoint = unsigned int;
	using mode_bit_fields =  glfw::mode_bitfields_t;//shift,ctrl,alt,super
	using on_char_with_modifier_entered_cb = void(*)(window_receiver, character_unicode_codepoint, mode_bit_fields);


	//==========================/ON_FILE(S)_DROPPED input
	using window_receiver = GLFWwindow * ;
	using files_count = int;
	using path_es = const char**;
	using on_file_s_dropped_cb = void(*)(window_receiver, files_count, path_es);


	//==========================/ON_MONITOR_CONNECTED
	using monitor = GLFWmonitor * ;
	using is_connected = glfw::connection_t;
	using on_monitor_connected_cb = void(*)(monitor, is_connected);


	//==========================/ON_JOYSTIC_CONNECTED input
	using joystic_slot_id = int;
	using is_connected = glfw::connection_t;
	using on_joystic_connected_cb = void(*)(joystic_slot_id, is_connected);
}