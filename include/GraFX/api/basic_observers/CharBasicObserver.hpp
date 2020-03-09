#pragma once
#include "basic/WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using CharBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void, callbacks::character_unicode_codepoint>;
}

