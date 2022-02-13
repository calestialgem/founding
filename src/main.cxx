// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "display.hxx"
#include "engine.hxx"
#include "event.hxx"

#include <GL/gl.h>
#include <iostream>
#include <memory>
#include <sstream>

int main()
{
	using namespace gecgelcem::founding;
	display::display const display{display::options{}};
	event::dispatcher      dispatcher;

	dispatcher.register_listener(
		event::type::DEBUG,
		[](event::event const &raw_event) {
			event::debug_event const &event =
				static_cast<event::debug_event const &>(raw_event);
			std::cout << event.message << std::endl;
		});

	auto const updater = [&display, &dispatcher](engine &engine) {
		display.update();
		dispatcher.dispatch_all();
		engine.enable_rendering(display.is_focused());
		if (display.is_closed()) {
			engine.close();
		}
	};

	auto const renderer = [&display](engine &engine) {
		glClearColor(
			display.is_focused(),
			display.is_iconified(),
			display.is_closed(),
			1.0);
		display.show();
	};

	auto const seconder = [&dispatcher](engine &engine) {
		std::cout << "Ticks:  " << engine.tick_stats().rate()
				  << "\nFrames: " << engine.frame_stats().rate() << std::endl;
		std::stringstream stream;
		stream << "Debug Message @" << engine.tick_stats().count();
		dispatcher.dispatch(
			std::move(std::make_unique<event::debug_event>(stream.str())));
	};

	engine{20.0, updater, renderer, seconder};
}
