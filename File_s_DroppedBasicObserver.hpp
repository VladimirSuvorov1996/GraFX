#pragma once
#include "WindowDependentBasicObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	using File_s_DroppedBasicObserver = WindowDependentBasicObserver<Implementation, invoke, void, callbacks::files_count, callbacks::path_es>;
}