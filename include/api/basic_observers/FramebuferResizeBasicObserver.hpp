#pragma once
#include "basic/WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using WindowFramebufferResizeBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void, callbacks::to_framebuffer_width, callbacks::to_framebuffer_height>;
}