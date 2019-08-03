#pragma once
#include "Constants.hxx"
namespace graFX {
	//An utility class, to interoperate with glfw 
	class Button {
	public:
		constexpr Button() = delete;
		constexpr Button(const Button&) = default;
		enum button : uint8_t { Left, Right, Middle, Button4, Button5, Button6, Button7, Last };
		constexpr Button(button button) :button_(button) {}

		//Maybe unsafe
		constexpr Button(glfw::button_t glfw_button) : button_(from_glfw_button(glfw_button)) {}



		button operator=(button button) { return (button_ = button); }
		Button operator=(Button oth) { button_ = oth.button_; return *this; }

		constexpr bool operator==(button button) const noexcept {
			return (button_ == button);
		}
		constexpr bool operator==(Button oth) const noexcept {
			return (button_ == oth.button_);
		}
		constexpr bool operator!=(button button) const noexcept {
			return (button_ != button);
		}
		constexpr bool operator!=(Button oth) const noexcept {
			return (button_ != oth.button_);
		}

		constexpr glfw::button_t code() const noexcept {
			return code(button_);
		}
		constexpr operator glfw::button_t() const noexcept {
			return code();
		}

		constexpr static glfw::button_t code(button button) noexcept {
			return glfw::buttons[button];
		}
	private:
		constexpr static button from_glfw_button(glfw::button_t glfw_button) {
			for (size_t index(Left); index < Last; ++index)
				if (code(static_cast<button>(index)) == glfw_button) 
					return static_cast<button>(index);
			return Last;
		}
	private:
		button button_;
	};
}