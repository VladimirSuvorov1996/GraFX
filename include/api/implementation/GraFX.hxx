#pragma once
#include <gsl-lite.hpp>
#include "CallbackSignatures.hxx"
#include "../implementation/CreationParameter.hxx"

namespace graFX {
	class GraFX {
	public:
		using procedure_name_t = gsl::czstring;
		static auto get_procedure_address(procedure_name_t procedure_name) {
			return glfwGetProcAddress(procedure_name);
		}

		//if we can use 
		static bool is_valid() { return is_valid_; }
		//true if initialized with the call, 
		//false - any other case
		static bool initialize() {
			if (is_valid_)return false;
			is_valid_ = (glfwInit() == true);
			return is_valid_;
		}
		static void set_parameter(CreationParameter parameter) {
			glfwInitHint(parameter.hint(), parameter.value());
		}

		//true if invalidated with the call,
		//false - any other case
		static bool dispose() {
			if (!is_valid_)return false;
			glfwTerminate();
			return (!(is_valid_ = false));
		}

		//instead of manual initialize|dispose, RAII based
		GraFX() { initialize(); }

		~GraFX() { dispose(); }


		struct version_t { int major, minor, revision; };
		static version_t get_version() {
			version_t ver_info;
			glfwGetVersion(&ver_info.major, &ver_info.minor, &ver_info.revision);
			return ver_info;
		}
		

		using version_string_t = gsl::czstring;
		static version_string_t get_version_string() { return glfwGetVersionString(); }

		static bool is_extension_supported(gsl::czstring extension) {
			return (glfwExtensionSupported(extension) == true);
		}

		static bool is_vulkan_supported() { return (glfwVulkanSupported() == true); }

		using instance_extensions_t = gsl::span<gsl::czstring>;
		static instance_extensions_t  get_required_instance_extensions() {
			uint32_t count;
			gsl::czstring* extensions = glfwGetRequiredInstanceExtensions(&count);
			return { extensions,count };
		}
		using on_error_cb = callbacks::on_error_cb;

		static on_error_cb on_error(on_error_cb callback) {
			return glfwSetErrorCallback(callback);
		}



	protected:
		inline static bool is_valid_ = false;
	};

	template<typename T>
	union graphic_output_tvec2 {
		struct { T x, y; };
		struct { T w, h; };
		struct Position { T x, y; } position;
		struct Size { T w, h; } size;

	};
	template<typename T>
	union graphic_output_trect2 {
		struct { T x, y, w, h; };
		struct {
			struct Position { T x, y; } position;
			struct Size { T w, h; } size;
		};
	};



	using graphic_output_tvec2i = graphic_output_tvec2<int>;
	using graphic_output_tvec2f = graphic_output_tvec2<float>;
	using graphic_output_trect2i = graphic_output_trect2<int>;

	static_assert(sizeof(graphic_output_tvec2i) == (2 * sizeof(int)));
	static_assert(sizeof(graphic_output_tvec2f) == (2 * sizeof(float)));
	static_assert(sizeof(graphic_output_trect2i) == (4 * sizeof(int)));
#ifndef GRAFX_DONT_USE_AUTOINITIALIZE
	namespace {
		static GraFX graphics;
	}
#endif // !GRAFX_DONT_USE_AUTOINITIALIZE
}