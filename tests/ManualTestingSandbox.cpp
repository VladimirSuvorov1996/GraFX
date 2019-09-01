#include <iostream>
#include <iomanip>
#include <vector>

#include <algorithm>
#include <fmt/printf.h>
using fmt::report_system_error;


#include "api/Window.hpp"
#include "api/GraFX.hpp"
#include "api/Clock.hpp"

#include "api/Joystic.hpp"
#include "api/basic_observers/JoysticBasicObserver.hpp"

#include "api/Monitor.hpp"
#include "api/EventDispatcher.hpp"
#include "api/basic_observers/basic/CallbackSignatures.hpp"
#include "api/basic_observers/ResizeBasicObserver.hpp"
#include "api/CreationParameter.hpp"
#include "api/Action.hpp"
#include "api/Connection.hpp"

#include "api/basic_observers/CursorMovedBasicObserver.hpp"
#include "api/basic_observers/CursorEnteredBasicObserver.hpp"

#include "api/basic_observers/ScrollBasicObserver.hpp"
#include "api/basic_observers/MouseButtonBasicObserver.hpp"

#include "api/basic_observers/KeyBasicObserver.hpp"
#include "api/basic_observers/CharBasicObserver.hpp"
#include "api/basic_observers/ModifiedCharBasicObserver.hpp"
#include "api/basic_observers/File_s_DroppedBasicObserver.hpp"


#include "api/basic_observers/ContentScaledBasicObserver.hpp"
#include "api/basic_observers/MaximizeBasicObserver.hpp"

#include "api/basic_observers/MonitorConnectedBasicObserver.hpp"
#include "api/basic_observers/ErrorBasicObserver.hpp"

class MonConnObserver {
public:
	void on_con(graFX::Monitor m, bool is_conn) {
		
	}
};

class ErrObserver {
public:
	void on_err(int code, std::string_view dsc) {
		
	}

};

GRAFX_REGISTRATE_OBSERVER_AS(ErrorBasicObserver, ErrObserver, on_err, EObserver);
GRAFX_REGISTRATE_OBSERVER_AS(MonitorConnectedBasicObserver, MonConnObserver, on_con, MCObserver);
graFX::Window makeWindow() {
	using namespace graFX;
	EObserver eo;
	GraFX::on_error(eo);

	Monitor mon(0);
	MCObserver mcob;
	Monitor::on_monitor_connected(mcob);


	//Monitor m(365);//NOTE: there is no 365-th monitor, but code works correctly
	WindowMaker maker;

	return maker
		<< MajorContextVersion{ 3 }
		<< MinorContextVersion{ 3 }
		<< ProfileMode{ ProfileMode::AnyProfile }
		<< Resizable{}
		<< Focused{}
		<< Maximized{}
	<< [&](auto& mk) {
		auto w = mk.make(320, 280, "TheWindow", &mon);
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

//TODO: Swap interval user pointer
//TODO: make proper support for structs CURSOR IMAGE VIDEOMODE GAMMARAMP WINDOW PROC ADDRESS e.t.c.
//TODO: <Window/Monitor>Traits -> to Window/Monitor
//TODO: Error Class for (GLFW_BLA_BLA_BLA_ERROR) (like Action, Key, Etc)

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

	Monitor mon(345);
	//std::cout<<"is_connected "<<mon.is_connected()<<std::endl;
	auto vs = mon.available_videomodes();
	std::cout<<"available_videomodes "<<vs.size()<<std::endl;
	
	auto s = mon.physical_size();
	std::cout<<"physical_size "<<s.h<<std::endl;


	Joystic j(0);
	
	std::cout<<"GUID: "<<j.GUID()<<std::endl;

	JObserver jo;
	j.on_joystic_connected(jo);


	auto bs = j.button_states();
	auto ps = j.present_axes();
	assert(bs.size());
	assert(ps.size());

	Window w = makeWindow();
	std::cout<<"Monitor is_connected: "<<w.properties().monitor().is_connected()<<std::endl;
	std::cout<<"Monitor name: "<<w.properties().monitor().name()<<std::endl;
	w.properties().monitor(mon, {0,0,320,240}, 60);
	assert(Window::get_current_context()->is_open());


	PrinterObserverCbn c;						// step 0: create an observer
	w.eventDispatcher().on_file_s_dropped(c);	// step 1: attach the created observer to the window
	//c.enabled(true);	// step 2: enable|disable observer (not required to enable, cos enabled by default; disable to make useless)
	


	assert(window::Mouse::CursorMode::Normal == w.mouse().cursor_mode());
	assert(false == w.mouse().sticky_mouse_buttons());
	assert(false == w.keyboard().sticky_keys());


	for (; w.is_open(); w.eventDispatcher().poll_events()) {
		w.render();
		if (w.keyboard().is_key_pressed(Key::Space)) {	
			w.request_attention();
		}
		if (w.keyboard().is_key_pressed(Key::Escape)) {	
			w.close();
		}
	};
}
