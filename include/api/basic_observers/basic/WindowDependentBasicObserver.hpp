#pragma once
#include "WindowDependent.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke, typename R, typename...As>
	class WindowDependentBasicObserver :
		public WindowDependent<invoke, Implementation, R, As...> 
	{};
}
#ifndef GRAFX_REGISTRATE_OBSERVER_AS_MACRO_DISABLE
#define GRAFX_REGISTRATE_OBSERVER_AS(OBSERVER_TYPE,IMPLEMENTATION,INVOKE,REGISTRATE_AS)\
using REGISTRATE_AS=graFX::input::OBSERVER_TYPE<IMPLEMENTATION,&IMPLEMENTATION::INVOKE>
#endif 