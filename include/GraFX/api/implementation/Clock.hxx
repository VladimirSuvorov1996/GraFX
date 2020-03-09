#pragma once
#include <GLFW\glfw3.h>
#include "GraFX/api/basic_observers/basic/ObserverCore.hpp"
class Clock {
public:
	using seconds = double;
	Clock(seconds time_multiplier = 1.f) { origin_ = create(time_multiplier); }
	Clock(const Clock& clock) {
		create();
		origin_ = clock.origin_;
	}
	Clock(Clock&& clock) {
		origin_ = clock.origin_;
		clock.origin_ =	create();
	}


	seconds elapsed() noexcept { 
		return  time_multiplier_ * (get_global_time() - origin_); 
	}
	seconds restart() noexcept {
		auto elapsed = Clock::elapsed();
		origin_ = get_global_time();
		return elapsed;
	}
	seconds time_multiplier()const noexcept { return time_multiplier_; }
	void time_multiplier(seconds m) noexcept { time_multiplier_ = m; }
	
	~Clock() { clocks_.remove(this); }

public:
	static void set_global_time(seconds start_point) noexcept {
		auto time_offset = start_point - get_global_time();
		for (auto clock : clocks_) 
			clock->origin_ += time_offset;
		glfwSetTime(start_point);
	}
	static seconds get_global_time() noexcept { return glfwGetTime(); }
	using Hz = uint64_t;
	static Hz get_global_timer_frequency() noexcept { return glfwGetTimerFrequency(); }
	using seconds_raw = uint64_t;
	static seconds_raw get_global_timer_value() noexcept { return glfwGetTimerValue(); }

protected:
	seconds create(seconds time_multiplier = 1.f) {
		clocks_.add(this);
		time_multiplier_ = time_multiplier;
		return get_global_time();
	}

protected:
	seconds origin_;
	seconds time_multiplier_ = 1.f;

protected:
	inline static graFX::input::observer_core::ObserverCore<Clock*> clocks_;
};