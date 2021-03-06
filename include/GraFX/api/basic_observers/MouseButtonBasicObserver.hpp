#pragma once
#include "basic/WindowDependentBasicObserver.hpp"
#include "../implementation/WindowMouse.hxx"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using MouseButtonBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void, callbacks::button, callbacks::is_pressed, callbacks::mode_bit_fields>;
}