#pragma once
#include "WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using WindowIconifyBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void, callbacks::is_iconified>;
}