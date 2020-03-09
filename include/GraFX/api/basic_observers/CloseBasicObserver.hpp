#pragma once
#include "basic/WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using WindowCloseBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void>;
}