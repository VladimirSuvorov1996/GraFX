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
			using namespace std;
			if (find(begin(), end(), to_pointer(observer)) == end())
				observers_.emplace_back(observer);
		}
		void remove(instance_t observer) {
			using namespace std;
			if (auto found = find(begin(), end(), to_pointer(observer)); found != end()) {
				swap(observers_[found-begin()], observers_.back());
				observers_.pop_back();
			}//observers_.erase(found, found + 1);
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
		using pointer_t =  std::conditional_t<std::is_pointer_v<T>, T, T*>;
		static constexpr pointer_t to_pointer(instance_t instance) {
			if constexpr (std::is_pointer_v<T>) {
				return instance;
			} else {
				return &instance;
			}
		}
	private:
		C<pointer_t> observers_;
	};
}