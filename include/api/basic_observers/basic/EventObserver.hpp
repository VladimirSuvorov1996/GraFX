#pragma once
#include "ObserverCore.hpp"
namespace graFX::input {
	using observer_core::ObserverCore;
	template<typename R, typename...As>
	class EventObserver {
	public:
		using base_t = EventObserver;//for derived classes we define base_t as this type
		using callback_t = R(*) (As...);
		static R on_notify(As...args) {
			for (auto observer : observers_)
				observer->callback(args...);
		}
		operator callback_t() const noexcept {
			return on_notify;
		}	
		void enabled(bool is_enabled) {
			(enabled_ = is_enabled) ? add_observer(this) : remove_observer(this);
		}
		bool enabled()const noexcept { return enabled_; }


	private:
		bool enabled_;
		void add_observer(EventObserver* observer) {
			observers_.add(observer);
		}
		void remove_observer(EventObserver* observer) {
			observers_.remove(observer);
		}
	protected:
		virtual ~EventObserver() {
			enabled(false);
		}
		virtual R callback(As...args) = 0;//you should overload this 
	private:
		static ObserverCore<EventObserver*> observers_;
	};
	template<typename R, typename...As>
	ObserverCore<EventObserver<R, As...>*> EventObserver<R, As...>::observers_;



}