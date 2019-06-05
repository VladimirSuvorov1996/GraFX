#pragma once
#include "CallbackSignatures.hxx"
#include "Key.hxx"
#include "KeyModifiers.hxx"
#include "WindowBased.hxx"
namespace graFX::window {
	class Keyboard : protected details::WindowBased {
	public:
		Keyboard(window_handle_ref_t base) : WindowBased(base) {}

		bool sticky_keys()const {
			return (is_valid()) ? glfwGetInputMode(window_handle_, glfw::input_modes[StickyKeys]) : false;
		}
		void sticky_keys(bool enabled) {
			if (is_valid())
				glfwSetInputMode(window_handle_, glfw::input_modes[StickyKeys], enabled);
		}


		bool is_key_pressed(Key key)const {
			return (glfwGetKey(window_handle_, key.code()) == glfw::KeyPressed);
		}

		



		//TODO: substitute following with listeners
		using on_key_cb = callbacks::on_key_cb;
		using on_char_entered_cb = callbacks::on_char_entered_cb;
		using on_char_with_modifier_entered_cb = callbacks::on_char_with_modifier_entered_cb;
		on_key_cb on_key(on_key_cb callback) {
			return glfwSetKeyCallback(window_handle_, callback);
		}
		on_char_entered_cb on_char(on_char_entered_cb callback) {
			return glfwSetCharCallback(window_handle_, callback);
		}
		on_char_with_modifier_entered_cb on_modified_char(on_char_with_modifier_entered_cb callback) {
			return glfwSetCharModsCallback(window_handle_, callback);
		}

	};
}