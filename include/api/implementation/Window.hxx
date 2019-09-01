#pragma once
#include "window_handle.hxx"
#include "GraFX.hxx"
#include "api/basic_observers/basic/ObserverCore.hpp"
#include "CallbackSignatures.hxx"
#include "Monitor.hxx"
#include "WindowKeyboard.hxx"
#include "WindowMouse.hxx"
#include "WindowProperties.hxx"
#include "WindowEventDispatcher.hxx"
#include "CreationParameter.hxx"//NOTE BEFORE WINDOW IS INCLUDED, so WindowMaker doesn't correct


namespace graFX {
	namespace details {
		//WindowScopedHandle changes window handle to specifed, until scope will be not exited.
		//At scope exit, restores previous window handle.

		template<class DerivedWindow>
		struct WindowTraits {
			using data_reference = DerivedWindow&;
			using handle_type = typename DerivedWindow::window_handle_t;

			static handle_type get_handle(data_reference data) {
				return data.window_handle_;
			}
			static void set_handle(data_reference data, handle_type handle) {
				data.window_handle_ = handle;
			}
		};

		template<class DerivedWindow>
		using WindowScopedHandle = ScopedHandle<WindowTraits<DerivedWindow>>;
	}
	class CurrentContext;


	
	class Window /*:
		protected WindowBased*/ {
	public:
		using window_handle_t = window_handle_t;
		using Keyboard = window::Keyboard;
		using Mouse = window::Mouse;
		using Properties = window::Properties;
		using EventDispatcher = window::EventDispatcher;
		using CreationParameter = CreationParameter;

	private:
		window_handle_t window_handle_ = nullptr;
	public:

		Keyboard keyboard() { return { window_handle_ }; }
		Mouse mouse() { return { window_handle_ }; }
		Properties properties() { return { window_handle_ }; }
		EventDispatcher eventDispatcher() { return { window_handle_ }; }
		//*CREATION
		Window() = default;
		Window(const Window&) = delete;
		//to a monitor create
		Window(int width, int height, const char* title, Monitor* monitor = nullptr) {
			create(width, height, title, monitor);
		}
		Window(Window&& src) :
			window_handle_(std::move(src.window_handle_))
		{
			src.window_handle_ = nullptr;
		}
		~Window() { invoke_set<glfwDestroyWindow>(window_handle_);  }
		//to a monitor create
		bool create(int width, int height, const char* title, Monitor* monitor=nullptr)	{
			if (GraFX::is_valid()) {
				if (is_open())close();
				window_handle_ = glfwCreateWindow(width, height, title, (monitor) ? monitor->monitor_handle_ : nullptr, nullptr);
			}
			return is_open();
		}
		void close() {
			invoke_set<glfwDestroyWindow>(window_handle_);
			window_handle_ = nullptr;
		}
		bool is_open()const { return (GraFX::is_valid()) ? (nullptr != window_handle_) : false; }

		void request_attention() {
			invoke_set<glfwRequestWindowAttention>(window_handle_);
		}

		static CurrentContext get_current_context();
		static void set_creation_parameter(CreationParameter parameter)	{
			glfwWindowHint(parameter.hint(), parameter.value());
		}

		//TODO: DECIDE if the function required
		static void set_string_creation_parameter(int key, gsl::czstring value) {
			glfwWindowHintString(key, value);
		}

		static void reset_creation_parameters() { glfwDefaultWindowHints(); }
		

		//~CREATION

		void render() { invoke_set<glfwSwapBuffers>(window_handle_); }


		static void set_render_interval(int interval) { glfwSwapInterval(interval); }

		void iconify() { invoke_set<glfwIconifyWindow>(window_handle_); }
		void maximize() { invoke_set<glfwMaximizeWindow>(window_handle_); }
		void restore() { invoke_set<glfwRestoreWindow>(window_handle_); }
		void set_context_current() { invoke_set<glfwMakeContextCurrent>(window_handle_); }
		void focus() { invoke_set<glfwFocusWindow>(window_handle_); }
		

	protected:
		template<auto callable, typename...Ts>
		void invoke_set(Ts&&...as) {
			if (is_open())std::invoke(callable, std::forward<Ts>(as)...);
		}

		Window(window_handle_t handle) :window_handle_(handle) {}
	protected:
		friend details::WindowTraits<Window>; //the main friend
		friend class CurrentContext; 
	};


	class CurrentContext {
	public:
		using current_context_window_t = Window;
		using current_context_window_ref_t = Window&;
		using current_context_window_cref_t = const Window & ;
		using current_context_window_ptr_t = Window * ;
		using current_context_window_cptr_t = const Window *;
		CurrentContext(const CurrentContext&) = default;
		CurrentContext(CurrentContext&&) = default;
		~CurrentContext() {
			current_context_window_.window_handle_ = nullptr;
		}
		void swapInterval(int interval) {
			glfwSwapInterval(interval);
		}

		current_context_window_ref_t operator*() noexcept { return current_context_window_; }
		current_context_window_cref_t operator*() const noexcept { return current_context_window_; }
		current_context_window_ptr_t operator->() noexcept { return &current_context_window_; }
		current_context_window_cptr_t operator->() const noexcept { return &current_context_window_; }
		operator current_context_window_ref_t() { return current_context_window_; }
		operator current_context_window_cref_t()const noexcept { return current_context_window_; }

	protected:
		current_context_window_t current_context_window_;
		CurrentContext(window_handle_t window_handle) {
			current_context_window_.window_handle_ = window_handle;
		}
		friend class current_context_window_t;
	};
	CurrentContext Window::get_current_context() {
		return { (GraFX::is_valid()) ? glfwGetCurrentContext() : nullptr };
	}



	class WindowMaker {//builder pattern
	public:
		using CreationParameter = graFX::CreationParameter;
		using this_reference = WindowMaker &;
		CreationParameter& operator[](size_t index) {
			return creation_parameters_[index];
		}
		const CreationParameter& operator[](size_t index)const {
			return creation_parameters_[index];
		}
		size_t size()const noexcept {
			return creation_parameters_.size();
		}
		bool empty()const noexcept {
			return creation_parameters_.empty();
		}
		this_reference clear() {
			creation_parameters_.clear();
			return *this;
		}

		Window make() {
			return make_window();
		}
		Window make(Window&& src) {
			return make_window(std::move(src));
		}
		Window make(int width, int height, const char* title, Monitor* monitor = nullptr) {
			return make_window(width, height, title, monitor);
		}
	private:
		template<typename...Ts>
		Window make_window(Ts&&...as) {			
			initialize_creation_parameters();
			return Window(std::forward<Ts>(as)...);
		}

		void initialize_creation_parameters() {
			Window::reset_creation_parameters();
			for (auto& creation_parameter : creation_parameters_)
				Window::set_creation_parameter(creation_parameter);
		}
	private:
		std::vector<CreationParameter> creation_parameters_;
		friend WindowMaker& operator<<(WindowMaker& maker, const CreationParameter& parameter);
	};
	WindowMaker& operator<<(WindowMaker& maker, const graFX::CreationParameter& parameter) {
		maker.creation_parameters_.emplace_back(parameter);
		return maker;
	}
	template<typename Callable>
	auto operator<<(WindowMaker& to, Callable callable)->decltype(std::invoke(callable, to)) {
		return std::invoke(callable, to);
	}
}
namespace graFX::details {
	using WindowScopedHandle_t = WindowScopedHandle<Window>;
}