#pragma once
#include "GraFX.hxx"
#include "Button.hxx"
#include "WindowBased.hxx"
namespace graFX::window {


	class TinyImage {
	public:
		using image_t = GLFWimage;
		using image_size_t = graphic_output_tvec2i;
		using pixel_components_array_t = gsl::span<uint8_t>;

		TinyImage(pixel_components_array_t pixel_components, image_size_t image_size) :
			pixel_components_(pixel_components),
			image_size_(image_size)
		{}
		void create(pixel_components_array_t pixel_components, image_size_t image_size) {
			pixel_components_ = pixel_components;
			image_size_ = image_size;
		}
		bool is_valid()const noexcept {
			return (image_size_.w*image_size_.h >= pixel_components_.size()/4);
		}
		image_size_t image_size()const noexcept {
			return image_size_;
		}
		pixel_components_array_t pixel_components()const noexcept {
			return pixel_components_;
		}
	protected:		
		image_size_t	image_size_;
		pixel_components_array_t pixel_components_;
	};
	class Mouse;
	//TODO: Implement this class
	class Cursor {
	public:
		using cursor_t = GLFWcursor;
		using cursor_pointer = GLFWcursor*;
		using const_cursor_pointer = const GLFWcursor*;
		Cursor(const Mouse& mouse) :
			mouse_(mouse),
			cursor_pointer_(nullptr)
		{}
		Cursor(Cursor&& src) :
			cursor_pointer_(src.cursor_pointer_),
			mouse_(src.mouse_)
		{
			src.cursor_pointer_ = nullptr;
		}
		Cursor(const Mouse& mouse, TinyImage image, int xhot, int yhot) :
			mouse_(mouse)
		{
			create(image, xhot, yhot);
		}
		void create(TinyImage image, int xhot, int yhot) {
			if (cursor_pointer_)return;
			TinyImage::image_t img ={
				image.image_size().w,
				image.image_size().h,
				image.pixel_components().data()
			};
			cursor_pointer_ = glfwCreateCursor(&img, xhot, yhot);
		}
		void create_standard(int shape) {
			if(!cursor_pointer_)cursor_pointer_ = glfwCreateStandardCursor(shape);
		}
		void reset() {
			if (!cursor_pointer_)return;
			glfwDestroyCursor(cursor_pointer_);
			cursor_pointer_ = nullptr;
		}
		bool is_valid()const noexcept {
			return cursor_pointer_;
		}
		
		enum Mode { Normal, Hiden, Disabled };
		Mode mode()const;
		void mode(Mode mode);
		

		void position(double x, double y);
		using position_t = graphic_output_tvec2<double>;
		position_t position()const;
		using on_cursor_moved_cb = callbacks::on_cursor_moved_cb;
		using on_cursor_enter_cb = callbacks::on_cursor_enter_cb;
		on_cursor_moved_cb on_moved(on_cursor_moved_cb callback);
		on_cursor_enter_cb on_entered(on_cursor_enter_cb callback);

		~Cursor() {
			reset();
		}
	protected:
		cursor_pointer cursor_pointer_;
		const Mouse& mouse_;
	protected:
		friend class Mouse;
	};


	class Mouse : 
		protected details::WindowBased 
	{
	public:
		using on_scroll_cb = callbacks::on_scroll_cb;
		using on_mouse_button_cb = callbacks::on_mouse_button_cb;

		Mouse(window_handle_ref_t base) : WindowBased(base) {}
		
		//buggy two
		bool sticky_mouse_buttons()const {
			return (is_valid()) ? glfwGetInputMode(window_handle_, glfw::input_modes[to_index(Mode::StickyMouseButtons)]) : false;
		}
		void sticky_mouse_buttons(bool enabled) {
			if (is_valid())glfwSetInputMode(window_handle_, glfw::input_modes[to_index(Mode::StickyMouseButtons)], enabled);
		}

		Cursor cursor()const {
			return Cursor{ *this };
		}
		void cursor(Cursor cursor) {
			glfwSetCursor(window_handle_, cursor.cursor_pointer_);
		}

		static bool raw_mouse_motion_supported() {
			return glfwRawMouseMotionSupported();
		}

		bool is_mouse_button_pressed(Button button)const {
			return (is_valid()) ? 
				(glfwGetMouseButton(window_handle_, button.code()) == glfw::KeyPressed) :
				false;
		}


		on_scroll_cb on_scroll(on_scroll_cb callback) {
			return invoke_get<glfwSetScrollCallback, on_scroll_cb>(nullptr, window_handle_, callback);
		}
		on_mouse_button_cb on_mouse_button(on_mouse_button_cb callback) {
			return invoke_get<glfwSetMouseButtonCallback, on_mouse_button_cb>(nullptr, window_handle_, callback);
		}
	protected:	
		//cursor		
		using CursorMode = Cursor::Mode;

		CursorMode cursor_mode()const {
			return (is_valid()) ?
				static_cast<CursorMode>((glfwGetInputMode(window_handle_, glfw::input_modes[to_index(Mode::Cursor)]) - glfw::cursor_modes[CursorMode::Normal])) :
				CursorMode::Normal;
		}
		void cursor_mode(CursorMode mode) {
			invoke_set<glfwSetInputMode>(window_handle_, glfw::input_modes[to_index(Mode::Cursor)], glfw::cursor_modes[mode]);
		}
		

		void set_cursor_position(double x, double y) {
			invoke_set<glfwSetCursorPos>(window_handle_, x, y);
		}
		using position_t = graphic_output_tvec2<double>;
		position_t get_cursor_position()const {
			position_t pos ={ 0,0 };
			invoke_set<glfwGetCursorPos>(window_handle_, &pos.x, &pos.y);
			return pos;
		}
				
		using on_cursor_moved_cb = Cursor::on_cursor_moved_cb;
		using on_cursor_enter_cb = Cursor::on_cursor_enter_cb;
		on_cursor_moved_cb on_cursor_moved(on_cursor_moved_cb callback) {
			return invoke_get<glfwSetCursorPosCallback, on_cursor_moved_cb>(nullptr, window_handle_, callback);
		}
		on_cursor_enter_cb on_cursor_entered(on_cursor_enter_cb callback) {
			return invoke_get<glfwSetCursorEnterCallback, on_cursor_enter_cb>(nullptr, window_handle_, callback);
		}
		//end cursor 
	private:
		friend class Cursor;
	};

	
		Cursor::Mode Cursor::mode()const {
			return mouse_.cursor_mode();
		}
		void Cursor::mode(Cursor::Mode mode) {
			const_cast<Mouse&>(mouse_).cursor_mode(mode);
		}
		

		void Cursor::position(double x, double y) {
			const_cast<Mouse&>(mouse_).set_cursor_position(x, y);
		}
		Cursor::position_t Cursor::position()const {
			return mouse_.get_cursor_position();
		}
		Cursor::on_cursor_moved_cb Cursor::on_moved(Cursor::on_cursor_moved_cb callback) {
			return const_cast<Mouse&>(mouse_).on_cursor_moved(callback);
		}
		Cursor::on_cursor_enter_cb Cursor::on_entered(Cursor::on_cursor_enter_cb callback) {
			return const_cast<Mouse&>(mouse_).on_cursor_entered(callback);
		}
}