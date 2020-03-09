#pragma once
#include "CallbackSignatures.hxx"
#include "Constants.hxx"
namespace graFX {
	struct KeyModifiers {
		enum { Shift, Ctrl, Alt, Super};

		bool shift : 2, ctrl : 2, alt : 2, super : 2;
		KeyModifiers() = delete;
		KeyModifiers(const KeyModifiers&) = default;

		KeyModifiers(callbacks::mode_bit_fields keyModifiersBitfield) :
			//glfw::m
			shift(keyModifiersBitfield&glfw::mode_bitfields[Shift]),
			ctrl(keyModifiersBitfield& glfw::mode_bitfields[Ctrl]),
			alt(keyModifiersBitfield& glfw::mode_bitfields[Alt]),
			super(keyModifiersBitfield& glfw::mode_bitfields[Super])
		{}

		const KeyModifiers& operator=(const KeyModifiers& oth) {
			shift = oth.shift;
			ctrl = oth.ctrl;
			alt = oth.alt;
			super = oth.super;
		}
		callbacks::mode_bit_fields operator=(callbacks::mode_bit_fields keyModifiersBitfield) {
			shift = (keyModifiersBitfield& glfw::mode_bitfields[Shift]);
			ctrl = (keyModifiersBitfield& glfw::mode_bitfields[Ctrl]);
			alt = (keyModifiersBitfield& glfw::mode_bitfields[Alt]);
			super = (keyModifiersBitfield& glfw::mode_bitfields[Super]);
			return keyModifiersBitfield;
		}
		callbacks::mode_bit_fields code()const noexcept {
			return (*reinterpret_cast<const uint8_t*>(this));
		}
		operator callbacks::mode_bit_fields()const noexcept {
			return code();
		}

		bool operator==(const KeyModifiers& oth)const {
			return (code() == oth.code());
		}
		bool operator!=(const KeyModifiers& oth)const {
			return (code() != oth.code());
		}

		bool operator==(callbacks::mode_bit_fields oth)const {
			return (code() == oth);
		}
		bool operator!=(callbacks::mode_bit_fields oth)const {
			return (code() != oth);
		}
	};
	static_assert(sizeof(KeyModifiers) == 1);
}