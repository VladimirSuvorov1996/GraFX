#pragma once
#include <string_view>
#include "basic/AutosubscribableObserver.hpp"
#include "basic/ImplementationDependentObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	class ErrorBasicObserver :
		public ImplementationDependentObserver<
		Implementation, 
		AutosubscribableObserver<void, callbacks::error_code, callbacks::error_text>, 
		invoke, 
		void, int, std::string_view> {
	protected:
		void callback(callbacks::error_code error_code, callbacks::error_text error_text) {
			using base_t = ImplementationDependentObserver<
				Implementation, 
				AutosubscribableObserver<void, callbacks::error_code, callbacks::error_text>, 
				invoke, 
				void, int, std::string_view>;

			base_t::invoke_callback(error_code, error_text);
		}
	};
}