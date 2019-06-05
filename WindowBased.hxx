#pragma once

namespace graFX::details {
	class WindowBased {
	protected:
		using window_handle_ref_t = window_handle_t &;
		WindowBased(window_handle_ref_t window_handle) :window_handle_(window_handle) {}
	protected:
		enum Mode { Cursor, StickyKeys, StickyMouseButtons };

		constexpr bool is_valid()const noexcept { return (nullptr != window_handle_); }
		window_handle_ref_t window_handle_;
	};


	//ScopedHandle changes window handle to specifed, until scope will be not exited.
	//At scope exit, restores previous window handle.

	template<class DerivedWindow>
	class ScopedHandle {
		using Window = DerivedWindow;
	public:
		ScopedHandle() = delete;
		ScopedHandle(Window& window, window_handle_t handle) {
			window_ = &window;
			handle_ = window_->window_handle_;
			window_->window_handle_ = handle;
		}
		~ScopedHandle() {
			window_->window_handle_ = handle_;
		}
	private:
		Window* window_;
		window_handle_t handle_;
	};

}
