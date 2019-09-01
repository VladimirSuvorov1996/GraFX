#pragma once
namespace graFX::details {
	template<typename Traits>
	class ScopedHandle {
		using data_reference = typename Traits::data_reference;
		using handle_type = typename Traits::handle_type;
	public:
		ScopedHandle() = delete;
		ScopedHandle(data_reference data, handle_type handle) :
			data_(data)
		{
			handle_ = Traits::get_handle(data_);
			Traits::set_handle(data_, handle);
		}
		~ScopedHandle() {
			Traits::set_handle(data_, handle_);
		}
	private:
		data_reference	data_;
		handle_type		handle_;
	};
}