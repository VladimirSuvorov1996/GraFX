#pragma once
#include "WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using WindowRefreshBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void>;
}