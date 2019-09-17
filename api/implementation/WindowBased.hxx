#pragma once
#include "ScopedHandle.hxx"
namespace graFX::details {
	class WindowBased {
	protected:
		using window_handle_ref_t = window_handle_t &;
		WindowBased(window_handle_ref_t window_handle) :window_handle_(window_handle) {}
	protected:
		enum class Mode { Cursor, StickyKeys, StickyMouseButtons };
		static constexpr size_t to_index(Mode mode) {
			return static_cast<size_t>(mode);
		}

		constexpr bool is_valid()const noexcept { return (nullptr != window_handle_); }
		
		template<auto callable, typename R, typename...Ts>
		R invoke_get(R defaultValue, Ts&&...as)const {			
			return (is_valid())?std::invoke(callable, std::forward<Ts>(as)...):defaultValue;
		}
		template<auto callable, typename...Ts>
		void invoke_set(Ts&&...as)const {			
			if(is_valid())std::invoke(callable, std::forward<Ts>(as)...);
		}
	protected:
		window_handle_ref_t window_handle_;
	};	

}
