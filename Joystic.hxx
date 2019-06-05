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
		using present_axes_t = gsl::span<const float>;

		static bool is_present(int joystic_at_slot) noexcept {
			return glfwJoystickPresent(joystic_at_slot);
		}

		Joystic(joystic_slot_id slot_id) :slot_id_(slot_id) {}
		joystic_slot_id slot_id()const noexcept { return slot_id_; }
		void slot_id(joystic_slot_id slot_id) noexcept { slot_id_ = slot_id; }
		bool is_valid()const noexcept { return is_present(slot_id_); }

		button_states_t button_states()const noexcept {
			return invoke<button_states_t, glfwGetJoystickButtons>();
		}
		name_t name()const noexcept {
			return glfwGetJoystickName(slot_id_);
		}
		present_axes_t present_axes()const noexcept {
			return invoke<present_axes_t, glfwGetJoystickAxes>();
		}

		//TODO: substitute with listener
		using on_joystic_connected_cb = callbacks::on_joystic_connected_cb;
		static on_joystic_connected_cb on_joystic_connected(on_joystic_connected_cb callback) {
			return glfwSetJoystickCallback(callback);
		}


	protected:
		template<typename Result, auto callable>
		Result invoke()const noexcept {
			int count;
			auto data = std::invoke(callable, slot_id_, &count);
			return { data,static_cast<size_t>(count) };
		}
	protected:
		
		joystic_slot_id slot_id_;
	};
}