#pragma once
#include "basic/WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using WindowRefreshBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void>;
}