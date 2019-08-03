#pragma once
#include "Constants.hxx"
namespace graFX::window {
	using Window_t = Window;

	class CreationParameter {
	public:
		constexpr CreationParameter() = delete;
		constexpr CreationParameter(const CreationParameter&) = default;

		using hint_t = int;
		using value_t = int;
		constexpr hint_t hint()const noexcept {
			return hint_;
		}
		value_t operator=(value_t value) {
			value_ = value;
			return value;
		}
		constexpr value_t value()const noexcept {
			return value_;
		}
	protected:
		constexpr CreationParameter(hint_t hint, value_t value) : hint_(hint), value_(value) {}
	private:
		hint_t hint_;
		value_t value_;
	};

	enum class creation_parameter_t {
		Focused, Iconified, Resizable, Visible, Decorated, Auto_iconify, Floating, Maximized, ProfileMode,
		MajorContextVersion, MinorContextVersion, ForwardCompatibility
	};


	namespace {
		template<creation_parameter_t parameter_>
		class CreationParameterBase : public CreationParameter {
		public:
			constexpr CreationParameterBase() = delete;
			constexpr CreationParameterBase(const CreationParameterBase&) = default;
			constexpr static creation_parameter_t parameter()noexcept {
				return parameter_;
			}
			constexpr static size_t index()noexcept {
				return static_cast<size_t>(parameter());
			}
		protected:
			constexpr CreationParameterBase(hint_t hint, value_t value) :
				CreationParameter(hint, value)
			{}
		};

		template<creation_parameter_t creation_parameter>
		class CreationFlag : public CreationParameterBase<creation_parameter> {
		public:
			using base_t = CreationParameterBase<creation_parameter>;
			constexpr CreationFlag(bool turn_on = true) :
				base_t(glfw::attributes[base_t::index()], turn_on)
			{}
		};
	}

	using Focused = CreationFlag<creation_parameter_t::Focused>;
	using Iconified = CreationFlag<creation_parameter_t::Iconified>;
	using Resizable = CreationFlag<creation_parameter_t::Resizable>;
	using Visible = CreationFlag<creation_parameter_t::Visible>;
	using Decorated = CreationFlag<creation_parameter_t::Decorated>;
	using Auto_iconify = CreationFlag<creation_parameter_t::Auto_iconify>;
	using Floating = CreationFlag<creation_parameter_t::Floating>;
	using Maximized = CreationFlag<creation_parameter_t::Maximized>;


	class ProfileMode : public CreationParameterBase<creation_parameter_t::ProfileMode> {
	public:
		using base_t = CreationParameterBase<creation_parameter_t::ProfileMode>;
		enum mode_t { AnyProfile, CoreProfile, CompatProfile };
		constexpr ProfileMode(mode_t mode) :
			base_t(glfw::attributes[base_t::index()], glfw::profile[mode])
		{}
	};

	namespace {
		template<creation_parameter_t creation_parameter>
		class ContextVersion : public CreationParameterBase<creation_parameter> {
		public:
			using base_t = CreationParameterBase<creation_parameter>;
			using value_t = CreationParameter::value_t;
			constexpr ContextVersion() = delete;
			constexpr ContextVersion(const ContextVersion&) = default;
			constexpr ContextVersion(value_t value) :
				base_t(glfw::attributes[base_t::index()], value)
			{}
		};
	}

	using MinorContextVersion = ContextVersion<creation_parameter_t::MinorContextVersion>;
	using MajorContextVersion = ContextVersion<creation_parameter_t::MajorContextVersion>;



//using Maximized = CreationFlag<creation_parameter_t::Maximized>;

	

}