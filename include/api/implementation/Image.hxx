#pragma once
#include "GraFX.hxx"
namespace graFX::window {

	class TinyImage {
	public:
		using image_t = GLFWimage;
		using image_size_t = graphic_output_tvec2i;
		using pixel_components_array_t = gsl::span<uint8_t>;

		TinyImage(pixel_components_array_t pixel_components, image_size_t image_size) :
			pixel_components_(pixel_components),
			image_size_(image_size) {}
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
		operator image_t()const {
			image_t image;
			image.width = image_size_.w;
			image.height = image_size_.h;
			image.pixels = pixel_components_.data();
			return image;
		}
	protected:
		image_size_t	image_size_;
		pixel_components_array_t pixel_components_;
	};
}