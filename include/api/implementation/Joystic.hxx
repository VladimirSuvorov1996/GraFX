#pragma once
#include <gsl-lite.hpp>
#include "CallbackSignatures.hxx"

namespace graFX::window {
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

		//TODO: substitute with listener
		using on_joystic_connected_cb = callbacks::on_joystic_connected_cb;
		static on_joystic_connected_cb on_joystic_connected(on_joystic_connected_cb callback) {
			return glfwSetJoystickCallback(callback);
		}
		
		
		GUID_t GUID()const {
			return invoke_get<glfwGetJoystickGUID, GUID_t>(nullptr, slot_id_);
		}
		
		bool is_gamepad()const {
			return invoke_get<glfwJoystickIsGamepad, bool>(false, slot_id_);
		}
		gamepad_name_t gamepad_name()const {
			return glfwGetGamepadName(slot_id_);
		}
		
		/*gamepad_name_t gamepad_name()const {
			return glfwGetGamepadName(slot_id_);
		}*/

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
		/*
		template<typename Result, auto callable>
		Result invoke_get()const noexcept {
			int count;
			auto data = std::invoke(callable, slot_id_, &count);
			return { data,static_cast<size_t>(count) };
		}
		*/
	protected:
		
		joystic_slot_id slot_id_;
	};
}