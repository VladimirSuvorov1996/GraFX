#pragma once
#include "WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using WindowCloseBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void>;
}