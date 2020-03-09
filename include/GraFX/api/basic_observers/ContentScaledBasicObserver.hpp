#pragma once
#include "basic/WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using WindowContentScaledBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void, callbacks::to_scale_x, callbacks::to_scale_y>;
}