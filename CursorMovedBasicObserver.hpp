#pragma once
#include "WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using CursorMovedBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void, callbacks::mouse_moved_to_x, callbacks::mouse_moved_to_y>;
}
