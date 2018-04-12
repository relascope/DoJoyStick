#ifndef LOOPER_H
#define LOOPER_H


#include <iostream>
// back-end
#include <boost/msm/back/state_machine.hpp>
//front-end
#include <boost/msm/front/state_machine_def.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

namespace smlooper {

	struct EventBase {};

	struct DBL_CLICK : EventBase {};
	struct CLICK : EventBase {};
	struct HOLD : EventBase {};
	struct DBL_HOLD : EventBase {};


#ifndef NDEBUG

#include <cxxabi.h>

		struct StateBase : public msm::front::state<> {
			template <class Event, class FSM>
			void on_entry(Event const& e, FSM&) {
				int status;
				char *demangled_event_name = abi::__cxa_demangle(typeid(e).name(),0,0,&status);
				char *demangled_state_name = abi::__cxa_demangle(typeid(this).name(), 0,0,&status);

				std::cout << demangled_event_name << " -> entering "  << demangled_state_name << std::endl;
				free (demangled_event_name);
				free (demangled_state_name);
			}

			template <class Event, class FSM>
			void on_exit(Event const& e, FSM&) {
				int status;
				char *demangled_event_name = abi::__cxa_demangle(typeid(e).name(),0,0,&status);
				char *demangled_state_name = abi::__cxa_demangle(typeid(this).name(), 0,0,&status);

				std::cout << demangled_event_name << " -> leaving "  << demangled_state_name << std::endl;
				free (demangled_event_name);
				free (demangled_state_name);
			}
		};
#else
		struct StateBase : public msm::front::state<> {};
#endif

	struct looper_ : public msm::front::state_machine_def<looper_> {
		struct Stopped : public StateBase {};
		struct Recording : public StateBase {};
		struct Playback : public StateBase{};
		struct Overdub : public StateBase {}; // TODO unused

		typedef Stopped initial_state;

		template <class Event>
		void start_playback(Event const&) {
			std::cout << "looper::start_playback" << std::endl;
		}

		template <class Event>
		void stop(Event const&) {
			std::cout << "looper::stop" << std::endl;
		}

		template <class Event>
		void start_recording(Event const&) {
			std::cout << "looper:start_recording" << std::endl;
		}

		template <class Event>
		void delete_loop(Event const&) {
			std::cout << "looper:delete_loop" << std::endl;
		}

		template <class Event>
		void undo_redo(Event const&) {
			std::cout << "looper:undo_redo" << std::endl;
		}

		typedef looper_ l;

		struct transition_table : mpl::vector<
				//    Start     Event         Next      Action				 Guard
				//  +---------+-------------+---------+---------------------+----------------------+

			a_row < Stopped , CLICK , Recording, &l::start_recording >
			, a_row < Stopped, HOLD , Stopped, &l::delete_loop>
			, a_row < Stopped, DBL_HOLD, Stopped, &l::delete_loop>
			, a_row < Stopped, DBL_CLICK, Stopped, &l::stop>

			, a_row < Recording, CLICK, Playback, &l::start_playback >
			, a_row < Recording, DBL_CLICK, Stopped, &l::stop >
			, a_row < Recording, HOLD, Recording, &l::undo_redo >
			, a_row < Recording, DBL_HOLD, Stopped, &l::delete_loop>

			, a_row < Playback, CLICK , Recording,   &l::start_recording >
			, a_row < Playback, DBL_CLICK, Stopped, &l::stop >
			, a_row < Playback, HOLD, Playback, &l::undo_redo >
			, a_row < Playback, DBL_HOLD, Stopped, &l::delete_loop>

				> {};

	};

	typedef msm::back::state_machine<looper_> looper;

}

#endif
