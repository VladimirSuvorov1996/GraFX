#pragma once
#include <array>
#include "CallbackSignatures.hxx"
#include "Constants.hxx"
namespace graFX {
	class Connection {
	public:
		using connected = callbacks::is_connected;
		Connection() : is_connected_(false) {}
		Connection(const Connection&) = default;
		Connection(connected c) :is_connected_(from_glfw_connection(c)) {}

		connected operator=(connected oth) {
			is_connected_ = from_glfw_connection(oth);
			return oth;
		}
		Connection operator=(Connection oth)noexcept {
			is_connected_ = oth.is_connected_;
			return *this;
		}

		bool operator==(connected oth)const noexcept {
			return (is_connected_ == oth);
		}
		bool operator!=(connected oth)const noexcept {
			return (is_connected_ != oth);
		}
		bool operator==(Connection oth)const noexcept {
			return (is_connected_ == oth.is_connected_);
		}
		bool operator!=(Connection oth)const noexcept {
			return (is_connected_ != oth.is_connected_);
		}

		connected code()const noexcept {
			return glfw::connection[is_connected_];
		}
		bool is_connected()const noexcept {
			return is_connected_;
		}
	private:
		static bool from_glfw_connection(connected c) {
			return (glfw::connection[true] == c);
		}
	private:
		 bool is_connected_;
	};
}

