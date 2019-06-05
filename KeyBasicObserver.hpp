#pragma once
#include "WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using KeyBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void, callbacks::key, callbacks::system_specific_scancode, callbacks::action, callbacks::mode_bit_fields>;
}
