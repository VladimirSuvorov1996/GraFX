#pragma once
namespace graFX::input::observer_core {
	template<typename T, template<typename...Ts>class C = std::vector>
	class ObserverCore {
	public:
		ObserverCore() = default;
		using instance_t =
			std::conditional_t<
			std::is_pointer_v<T>,
			T,
			T&>;

		void add(instance_t observer) {
			if (std::find(std::begin(observers_), std::end(observers_), observer) == std::end(observers_))
				observers_.emplace_back(observer);
		}
		void remove(instance_t observer) {
			if (auto found = std::find(std::begin(observers_), std::end(observers_), observer); found != std::end(observers_))
				observers_.erase(found, found + 1);
			else observers_.shrink_to_fit();
		}

		const C<T>& view()const noexcept {
			return observers_;
		}
		operator C<T>& () noexcept {
			return observers_;
		}
		operator const C<T>& ()const noexcept {
			return observers_;
		}

		decltype(auto) begin() noexcept {
			return observers_.begin();
		}
		decltype(auto) end() noexcept {
			return observers_.end();
		}
		decltype(auto) rbegin() noexcept {
			return observers_.rbegin();
		}
		decltype(auto) rend() noexcept {
			return observers_.rend();
		}
		decltype(auto) cbegin()const noexcept {
			return observers_.cbegin();
		}
		decltype(auto) cend()const noexcept {
			return observers_.cend();
		}
		decltype(auto) crbegin()const noexcept {
			return observers_.crbegin();
		}
		decltype(auto) crend()const noexcept {
			return observers_.crend();
		}

	private:
		C<T> observers_;
	};
}