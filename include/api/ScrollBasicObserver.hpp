#pragma once
#include "WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using ScrollBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void, callbacks::offset_x, callbacks::offset_y>;
}
