// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "display.hxx"
#include "engine.hxx"
#include "event.hxx"

#include <GL/gl.h>
#include <iostream>
#include <memory>
#include <sstream>

using namespace gecgelcem::founding;

static event::type const DEBUG_EVENT;

struct debug_event : event::base {
	std::string message;

	debug_event(std::string &&message)
		: message{std::move(message)}
	{
	}

	event::type type() const noexcept override
	{
		return DEBUG_EVENT;
	}
};

int main()
{
	display::display const display{display::options{}};

	DEBUG_EVENT.listener([](event::base const &raw_event) {
		debug_event const &event = static_cast<debug_event const &>(raw_event);
		std::cout << event.message << std::endl;
	});

	auto const updater = [&display](engine &engine) {
		display.update();
		event::dispatch();
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

	auto const seconder = [](engine &engine) {
		std::cout << "Ticks:  " << engine.tick_stats().rate()
				  << "\nFrames: " << engine.frame_stats().rate() << std::endl;
		std::stringstream stream;
		stream << "Debug Message @" << engine.tick_stats().count();
		event::queue(std::move(std::make_unique<debug_event>(stream.str())));
	};

	engine{20.0, updater, renderer, seconder};
}
