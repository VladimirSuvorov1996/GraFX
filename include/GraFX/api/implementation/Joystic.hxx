#pragma once
#include "guidelines_support_library_selector.hxx"
#include "CallbackSignatures.hxx"

namespace graFX::window {
	class JoysticHats {
	public:
		enum hat_state {
			Centred = 0,
			Up = 1,
			Right = Up<<1,
			Down = Right<<1,
			Left = Down<<1,
			RightUp = Right|Up,
			RightDown = Right|Down,
			LeftUp = Left|Up,
			LeftDown = Left|Down
		};
	public:
		auto operator[](size_t hat_index)const {
			return [=] (hat_state current_hat_state)->bool {
				return (hats_[hat_index] & current_hat_state);
			};
		}
	private:
		JoysticHats(gsl::span<const uint8_t> hats) :
			hats_(hats)
		{}
	private:
		gsl::span<const uint8_t> hats_;
		friend class Joystic;
	};
	struct GamepadState {


		static constexpr size_t ButtonsCount = 15;
		static constexpr size_t AxesCount = 6;
		bool is_present_and_has_gamepad_mapping;
		bool is_pressed[ButtonsCount];
		float axis_value[AxesCount];		
	};

	class Joystic {
	public:
		using joystic_slot_id = callbacks::joystic_slot_id;
		using size_t = std::size_t;
		using button_states_t = gsl::span<const unsigned char>;
		using name_t = gsl::czstring;
		using GUID_t = gsl::czstring;
		using gamepad_name_t = gsl::czstring;
		using present_axes_t = gsl::span<const float>;

		static bool is_present(int joystic_at_slot) noexcept {
			return glfwJoystickPresent(joystic_at_slot);
		}

		Joystic(joystic_slot_id slot_id) :slot_id_(slot_id) {}
		joystic_slot_id slot_id()const noexcept { return slot_id_; }
		void slot_id(joystic_slot_id slot_id) noexcept { slot_id_ = slot_id; }
		bool is_valid()const noexcept { return is_present(slot_id_); }

		button_states_t button_states()const noexcept {
			int count = 0;
			auto axes = invoke_get<glfwGetJoystickButtons, const unsigned char*>(nullptr, slot_id_, &count);
			return { axes,static_cast<size_t>(count) };

		//	return invoke_get<button_states_t, glfwGetJoystickButtons>();
		}
		name_t name()const noexcept {
			return invoke_get<glfwGetJoystickName, name_t>(nullptr, slot_id_);
		}
		present_axes_t present_axes()const noexcept {
			int count = 0;
			auto axes = invoke_get<glfwGetJoystickAxes, const float*>(nullptr, slot_id_, &count);
			return { axes,static_cast<size_t>(count) };
		}


		using on_joystic_connected_cb = callbacks::on_joystic_connected_cb;
		static on_joystic_connected_cb on_joystic_connected(on_joystic_connected_cb callback) {
			return glfwSetJoystickCallback(callback);
		}
		GamepadState state()const {
			GamepadState state;
			GLFWgamepadstate gamepad_state;
			state.is_present_and_has_gamepad_mapping = (invoke_get<glfwGetGamepadState, int>(0, slot_id_, &gamepad_state) != 0);
			if (state.is_present_and_has_gamepad_mapping) {
				for (size_t axis_index(0); axis_index<state.AxesCount; ++axis_index)
					state.axis_value[axis_index] = gamepad_state.axes[axis_index];
				for (size_t button_index(0); button_index<state.ButtonsCount; ++button_index)
					state.is_pressed[button_index] = (gamepad_state.buttons[button_index] == glfw::KeyPressed);
			}
			return state;
		}
		
		GUID_t GUID()const {
			return invoke_get<glfwGetJoystickGUID, GUID_t>(nullptr, slot_id_);
		}
		
		
		JoysticHats get_joystic_hats()const {
			int count = 0;
			auto hats = invoke_get<glfwGetJoystickHats, const uint8_t*>(nullptr, slot_id_, &count);
			return JoysticHats({ hats, static_cast<size_t>(count) });
		}

		bool has_gamepad_mapping()const {
			return invoke_get<glfwJoystickIsGamepad, bool>(false, slot_id_);
		}
		gamepad_name_t gamepad_name()const {
			return glfwGetGamepadName(slot_id_);
		}

		static bool update_gamepad_mappings(gsl::czstring gamepad_mapping_ascii_string) {
			return glfwUpdateGamepadMappings(gamepad_mapping_ascii_string);
		}

		using user_data_pointer_t = void*;
		void set_user_pointer(user_data_pointer_t user_data) {
			invoke_set<glfwSetJoystickUserPointer>(slot_id_, user_data);
		}
		user_data_pointer_t get_user_pointer() {
			return invoke_get<glfwGetJoystickUserPointer, user_data_pointer_t>(nullptr, slot_id_);
		}


	protected:		
		template<auto callable, typename R, typename...Ts>
		R invoke_get(R defaultValue, Ts&&...as)const {			
			return (is_valid())?std::invoke(callable, std::forward<Ts>(as)...):defaultValue;
		}
		template<auto callable, typename...Ts>
		void invoke_set(Ts&&...as)const {			
			if(is_valid())std::invoke(callable, std::forward<Ts>(as)...);
		}
	protected:
		
		joystic_slot_id slot_id_;
	};



}

