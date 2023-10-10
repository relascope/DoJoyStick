//#ifndef DOJOYSTICKLOOPER_HPP
//#define DOJOYSTICKLOOPER_HPP
//
//#include <iostream>
//
//#include "jsevent.h"
//#include "loopersm.hpp"
//
//using namespace smlooper;
//
//static char const* const state_names[] = {"Stopped", "Recording", "Playback", "Overdub", "StoppedWithLoop"};
//
//class DoJoyStickLooper {
//public:
//
//	DoJoyStickLooper() {
//		init();
//	}
//
//	void start() {
//		_looper.start();
//
//		_events.setEventHandler(&DoJoyStickLooper::looperEventHandler, this);
//		_events.startJoystickEvents();
//	}
//
//	static void looperEventHandler(JsEvents::CLICK_TYPE clickType, void * data) {
//		// TODO checking for null and conversion error...
//		DoJoyStickLooper *_this = static_cast<DoJoyStickLooper*> (data);
//
//		switch (clickType) {
//			case JsEvents::SINGLE:
//				_this->_looper.process_event(smlooper::CLICK());
//				break;
//			case JsEvents::DOUBLE:
//				_this->_looper.process_event( smlooper::DBL_CLICK());
//				break;
//			case JsEvents::HOLD:
//				_this->_looper.process_event(smlooper::HOLD());
//				break;
//			case JsEvents::DOUBLE_HOLD:
//				_this->_looper.process_event(smlooper::DBL_HOLD());
//				break;
//			default:
//				throw "Undefinded ClickType";
//				break;
//		}
//
//		_this->pstate();
//	}
//
//	virtual ~DoJoyStickLooper() {
//		_looper.stop();
//	}
//
//private:
//	looper _looper;
//	JsEvents _events;
//
//	void init() {
//#ifndef NDEBUG
//		std::cout << "Clearing loops to add a single one. Compile with -DNDEBUG to avoid debugging behaviour!" << std::endl;
//		system("oscsend osc.udp://localhost:9951 /loop_del i -1");
//		system("oscsend osc.udp://localhost:9951 /loop_add ii 2 0");
//#endif
//	}
//
//	void pstate() const {
//		std::cout << " -> " << state_names[_looper.current_state()[0]] << std::endl;
//	}
//};
//
//#endif // DOJOYSTICKLOOPER_HPP
