#pragma once
#include "basic/WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using WindowFocusBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void, callbacks::is_focused>;
}