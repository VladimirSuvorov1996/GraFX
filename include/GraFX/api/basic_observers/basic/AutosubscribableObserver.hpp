#pragma once
#include "EventObserver.hpp"
namespace graFX::input {
	template<typename R, typename...As>
	class AutosubscribableObserver :
		public EventObserver<R, As...>{
	public:
		AutosubscribableObserver() {
			EventObserver<R, As...>::base_t::enabled(true);
		}
	};
}