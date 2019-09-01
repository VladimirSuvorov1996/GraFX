#pragma once
#include "basic/WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using WindowMoveBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void, callbacks::to_x, callbacks::to_y>;
}