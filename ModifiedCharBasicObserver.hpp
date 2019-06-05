#pragma once
#include "WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using ModifiedCharBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void, callbacks::character_unicode_codepoint, callbacks::mode_bit_fields>;
}

