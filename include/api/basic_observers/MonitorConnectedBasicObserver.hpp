#pragma once
#include "../Monitor.hpp"
#include "basic/AutosubscribableObserver.hpp"
#include "basic/ImplementationDependentObserver.hpp"
namespace graFX::input {
	template<typename Implementation, auto invoke>
	class MonitorConnectedBasicObserver :
		public ImplementationDependentObserver<
		Implementation, 
		AutosubscribableObserver<void, callbacks::monitor, callbacks::is_connected>, 
		invoke, 
		void, Monitor&, bool> {
	protected:
		void callback(callbacks::monitor m, callbacks::is_connected is_connected) {
			using base_t = ImplementationDependentObserver<
				Implementation, 
				AutosubscribableObserver<void, callbacks::monitor, callbacks::is_connected>, 
				invoke, 
				void, Monitor&, bool>;

			Monitor current_monitor;
			details::MonitorScopedHandle_t scope(current_monitor, m);
			base_t::invoke_callback(current_monitor, is_connected);
		}
	};

} 