#pragma once
#include "ImplementationDependentObserver.hpp"
#include "CallbackSignatures.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	class JoysticBasicObserver :
		public ImplementationDependentObserver<
		Implementation,		
		AutosubscribableObserver<void, callbacks::joystic_slot_id, callbacks::is_connected>,
		invoke,
		void, callbacks::joystic_slot_id, callbacks::is_connected> {
	protected:
		void callback(callbacks::joystic_slot_id joy, callbacks::is_connected is) {
			using base_t = ImplementationDependentObserver<
				Implementation,
				AutosubscribableObserver<void, callbacks::joystic_slot_id, callbacks::is_connected>,
				invoke,
				void, callbacks::joystic_slot_id, callbacks::is_connected>;

			base_t::invoke_callback(joy, is);
		}
	};
}