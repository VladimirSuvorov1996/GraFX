#include <iostream>
#include <iomanip>
#include <vector>

#include <algorithm>
#include <fmt/printf.h>
using fmt::report_system_error;


#include "Window.hpp"
#include "GraFX.hpp"
#include "Clock.hpp"

#include "Joystic.hpp"
#include "JoysticBasicObserver.hpp"

#include "Monitor.hpp"
#include "EventDispatcher.hpp"
#include "CallbackSignatures.hpp"
#include "ResizeBasicObserver.hpp"
#include "CreationParameter.hpp"
#include "Action.hpp"
#include "Connection.hpp"

#include "CursorMovedBasicObserver.hpp"
#include "CursorEnteredBasicObserver.hpp"

#include "ScrollBasicObserver.hpp"
#include "MouseButtonBasicObserver.hpp"

#include "KeyBasicObserver.hpp"
#include "CharBasicObserver.hpp"
#include "ModifiedCharBasicObserver.hpp"
#include "File_s_DroppedBasicObserver.hpp"

graFX::Window makeWindow() {
	using namespace graFX;
	Monitor m(365);//NOTE: there is no 365-th monitor, but code works correctly
	WindowMaker maker;

	return maker
		<< MajorContextVersion{ 3 }
		<< MinorContextVersion{ 3 }
		<< ProfileMode{ ProfileMode::AnyProfile }
		<< Resizable{}
		<< Focused{}
	<< [&](auto& mk) {
		auto w = mk.make(320, 280, "TheWindow", &m);
		w.set_context_current();
		w.focus();
		return w;
	};
}

using namespace graFX::input;
class CustomObserver {
public://NOTE: pathes are UTF encoded
	void on_files_dropped(graFX::Window& w, callbacks::files_count c, callbacks::path_es pathes) {
		for (size_t index(0); index < c; ++index)
			std::cout << pathes[index] << std::endl;		
	}
};
GRAFX_REGISTRATE_OBSERVER_AS(File_s_DroppedBasicObserver, CustomObserver, on_files_dropped, PrinterObserverCbn);

#include <Windows.h>

//TODO: Monitor listeners
//TODO: GraFX Error listeners
//TODO: Swap interval user pointer
//TODO: make proper support for structs CURSOR IMAGE VIDEOMODE GAMMARAMP WINDOW PROC ADDRESS e.t.c.


class CustomJoysticObserver {
public:
	void on_joyconnected(callbacks::joystic_slot_id id, graFX::Connection c) {
		std::cout << "joystick with id = " << id << " was " << ((c.is_connected()) ? "" : "dis") << "connected" << std::endl;
	}
};

GRAFX_REGISTRATE_OBSERVER_AS(JoysticBasicObserver, CustomJoysticObserver, on_joyconnected, JObserver);

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);//to test if files are dropped, 
	SetConsoleOutputCP(1251);//UTF encoding
	setlocale(LC_ALL, "RUS");//must be enabled;


	using namespace graFX;

	Joystic j(0);

	JObserver jo;
	j.on_joystic_connected(jo);


	auto bs = j.button_states();
	auto ps = j.present_axes();
	assert(bs.size());
	assert(ps.size());

	Window w = makeWindow();

	assert(Window::get_current_context()->is_open());


	PrinterObserverCbn c;						// step 0: create an observer
	w.eventDispatcher().on_file_s_dropped(c);	// step 1: attach the created observer to the window
	//c.enabled(true);	// step 2: enable|disable observer (not required to enable, cos enabled by default; disable to make useless)
	


	assert(window::Mouse::CursorMode::Normal == w.mouse().cursor_mode());
	assert(false == w.mouse().sticky_mouse_buttons());
	assert(false == w.keyboard().sticky_keys());


	for (; w.is_open(); w.eventDispatcher().poll_events()) {
		w.render();
		if (w.keyboard().is_key_pressed(Key::Escape))
			w.close();
		
	};
}
