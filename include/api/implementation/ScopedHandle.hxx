#pragma once
namespace graFX::details {
	template<typename T>
	class ScopedHandle {
		using type			= T;
		using traits		= typename type::traits;
		using reference		= typename traits::reference;
		using pointer		= typename traits::pointer;
		using handle_type	= typename traits::handle_type;
	public:
		ScopedHandle() = delete;
		ScopedHandle(ScopedHandle&& src) :
			data_(src.data_),
			handle_(src.handle_)
		{	src.data_ = nullptr;	}
		ScopedHandle(reference data) :
			data_(&data) {
		}
		ScopedHandle(reference data, handle_type handle) :
			data_(&data) {
			set(handle);
		}
		void set(handle_type handle) {
			if (!data_)return;
			handle_ = traits::get_handle(*data_);
			traits::set_handle(*data_, handle);
		}
		void reset() {			
			if (!data_)return;
			traits::set_handle(*data_, handle_);
			data_ = nullptr;
		}
		~ScopedHandle() {
			reset();
		}
	private:
		pointer			data_;
		handle_type		handle_;
	};
	template<typename T, typename H>
	ScopedHandle<T> set_scoped_handle(T& data, H handle) {
		return { data, handle };
	}

#ifndef	GRAFX_DONT_USE_CAPTURE_SCOPED_HANDLE
	#define GRAFX_CAPTURE_SCOPED_HANDLE(DATA, HANDLE)\
		auto scoped_handle = details::set_scoped_handle(DATA, HANDLE)
#endif
}