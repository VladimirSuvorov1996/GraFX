#pragma once
#include "Constants.hxx"
namespace graFX {
	//An utility class, to interoperate with glfw 
	class Key {
	public:
		constexpr Key() = delete;
		constexpr Key(const Key&) = default;
		enum key : uint8_t {
			Space,
			Apostrophe,
			Comma,
			Minus,
			Period,
			Slash,
			Key0, Key1, Key2, Key3, Key4,
			Key5, Key6, Key7, Key8, Key9,
			Semicolon,
			Equal,
			A, B, C, D, E, F, G, H, I, J, K, L, M,
			N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			LeftBracket,
			BackSlash,
			RightBracket,
			GraveAccent,

			World1, World2,
			/* Function keys */
			Escape,
			Enter,
			Tab,
			Backspace,
			Insert,
			Delete,
			Right,
			Left,
			Down,
			Up,
			PageUp,
			PageDown,
			Home,
			End,
			CapsLook,
			ScrollLook,
			NumLook,
			PrintScreen,
			Pause,

			F1, F2, F3, F4, F5,
			F6, F7, F8, F9, F10,
			F11, F12, F13, F14, F15,
			F16, F17, F18, F19, F20,
			F21, F22, F23, F24, F25,

			Num0, Num1, Num2, Num3, Num4,
			Num5, Num6, Num7, Num8, Num9,
			NumDecimal,
			NumDivide,
			NumMultiply,
			NumSubtract,
			NumAdd,
			NumEqual,
			NumEnter,

			LeftShift,
			LeftControl,
			LeftAlt,
			LeftSuper,

			RightShift,
			RightControl,
			RightAlt,
			RightSuper,

			Menu,

			Last
		};
		constexpr Key(key key) :key_(key) {}

		//Maybe unsafe
		constexpr Key(glfw::key_t glfw_key) : key_(from_glfw_key(glfw_key)) {}

		key operator=(key key) { return (key_ = key); }
		Key operator=(Key oth) { key_ = oth.key_; return *this; }

		constexpr bool operator==(key key) const noexcept {
			return (key_ == key);
		}
		constexpr bool operator==(Key oth) const noexcept {
			return (key_ == oth.key_);
		}
		constexpr bool operator!=(key key) const noexcept {
			return (key_ != key);
		}
		constexpr bool operator!=(Key oth) const noexcept {
			return (key_ != oth.key_);
		}

		constexpr glfw::key_t code() const noexcept {
			return code(key_);
		}
		constexpr operator glfw::key_t() const noexcept {
			return code();
		}

		constexpr static glfw::key_t code(key key) noexcept {
			return glfw::keys[key];
		}
	private:
		constexpr static key from_glfw_key(glfw::key_t glfw_key) {
			for (size_t index(Space); index < Last; ++index)
				if (code(static_cast<key>(index)) == glfw_key)
					return static_cast<key>(index);
			return Last;
		}
	private:
		key key_;
	};
}