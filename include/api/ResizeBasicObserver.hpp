#pragma once
#include "WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using WindowResizeBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void, callbacks::to_width, callbacks::to_height>;
}