#pragma once
#include "../../implementation/window_handle.hxx"
#include "../../Window.hpp"
#include "AutosubscribableObserver.hpp"
#include "implementationDependentObserver.hpp"
#include "../implementation/ScopedHandle.hxx"
namespace graFX::input {
	template<auto invoke, typename Implementation, typename R, typename...As>
	class WindowDependent :
		public ImplementationDependentObserver<
		Implementation, 
		AutosubscribableObserver<R, window_handle_t, As...>, 
		invoke, 
		R, Window&, As...> {
	protected:
		R callback(window_handle_t w, As...as) {
			using base_t = ImplementationDependentObserver<
				Implementation, 
				AutosubscribableObserver<R, window_handle_t, As...>, 
				invoke, 
				R, Window&, As...>;

			Window current_window;
			GRAFX_CAPTURE_SCOPED_HANDLE(current_window, w);
			base_t::invoke_callback(current_window, std::forward<As>(as)...);
		}
	};
}