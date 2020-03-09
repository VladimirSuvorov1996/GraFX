#pragma once
#include <string_view>
#include "CallbackSignatures.hxx"
#include "Constants.hxx"
namespace graFX {
	class Error {
	public:
		enum ErrorType : uint8_t {
			NoError,
			NotInitialized,
			NoCurrentContext,
			InvalidEnum,
			InvalidValue,
			OutOfMemory,
			ApiUnavailable,
			VersionUnavailable,
			PlatformError,
			FormatUnavailable,
			NoWindowContext,
			ErrorTypesCount
		};
		constexpr Error(glfw::error_t error_code, const char* description) :
			description_(description), 
			error_type_(from_glfw_error_code(error_code))
		{}
		constexpr Error(glfw::error_t error_code, std::string_view description) :
			description_(description.data()), 
			error_type_(from_glfw_error_code(error_code))
		{}
		static Error get_last_error() {
			const char* description = nullptr;
			glfw::error_t error_code = glfwGetError(&description);
			return Error{ error_code, description };
		}
		constexpr ErrorType type()const {
			return error_type_;
		}
		constexpr const char* description()const {
			return description_;
		}
		constexpr glfw::error_t code()const {
			return code(error_type_);
		}
		

		Error operator=(Error oth) { 
			error_type_ = oth.error_type_; 
			description_ = oth.description_;
			return *this; 
		}


		constexpr bool operator == (glfw::error_t error_code)const {
			return code() == error_code;
		}
		constexpr bool operator != (glfw::error_t error_code)const {
			return code() != error_code;
		}
		constexpr bool operator == (Error error)const {
			return code() == error.code();
		}
		constexpr bool operator != (Error error)const {
			return code() != error.code();
		}
		static constexpr glfw::error_t code(ErrorType error_type) {
			return glfw::errors[error_type];
		}
		constexpr operator glfw::error_t ()const {
			return code();
		}

	private:	
		static constexpr ErrorType from_glfw_error_code(glfw::error_t error_code) {
			for (uint8_t error_type_index(NoError); error_type_index<ErrorTypesCount; ++error_type_index)
				if (error_code & glfw::errors[static_cast<ErrorType>(error_type_index)])
					return static_cast<ErrorType>(error_type_index);
			return NoError;
		}
	private:
		ErrorType error_type_;
		const char* description_;
	};

}