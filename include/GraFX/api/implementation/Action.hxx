#pragma once
#include "CallbackSignatures.hxx"
#include "Constants.hxx"
namespace graFX {
	class Action {
	public:
		enum action : uint8_t { Release, Press, Repeat, Last };
		Action() : action_(Release) {}
		Action(const Action&) = default;
		Action(callbacks::action a) :action_(from_glfw_action(a)) {}

		action operator=(action oth)noexcept {
			action_ = oth;
			return oth;
		}
		callbacks::action operator=(callbacks::action oth) {
			action_ = from_glfw_action(oth);
			return oth;
		}
		const Action& operator=(const Action& oth)noexcept {
			action_ = oth.action_;
			return *this;
		}

		bool operator==(action oth)const noexcept {
			return (action_ == oth);
		}
		bool operator!=(action oth)const noexcept {
			return (action_ != oth);
		}
		bool operator==(const Action& oth)const noexcept {
			return (action_ == oth.action_);
		}
		bool operator!=(const Action& oth)const noexcept {
			return (action_ != oth.action_);
		}
		bool operator==(callbacks::action oth)const {
			return (action_ == from_glfw_action(oth));
		}
		bool operator!=(callbacks::action oth)const {
			return (action_ != from_glfw_action(oth));
		}

		callbacks::action code()const noexcept {
			return glfw::actions[action_];
		}
		operator callbacks::action()const noexcept {
			return code();
		}
	private:
		static action from_glfw_action(callbacks::action glfw_action) {
			for (auto index(0); index < Last; ++index)
				if (glfw_action == glfw::actions[index])
					return static_cast<action>(index);
			return Last;
		}
	private:
		action action_;
	};
}
