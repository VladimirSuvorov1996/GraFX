#pragma once
#include "AutosubscribableObserver.hpp"
namespace graFX::input {

	template<typename Implementation, typename BasicObserver, auto invoke, typename R, typename...As>
	class ImplementationDependentObserver :
		public Implementation, 
		public BasicObserver {
	protected:
		R invoke_callback(As...as) {
			(this->*invoke)(std::forward<As>(as)...);
		}
	};
}