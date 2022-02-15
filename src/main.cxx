// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "display.hxx"
#include "engine.hxx"
#include "event.hxx"

#include <iostream>

using namespace gecgelcem::founding;

static event::type const SECOND_EVENT;

struct second_event : event::base {
	statistics ticks;
	statistics frames;

	second_event(statistics ticks, statistics frames)
		: ticks{ticks}
		, frames{frames}
	{
	}

	event::type type() const noexcept override
	{
		return SECOND_EVENT;
	}
};

int main()
{
	display::display const display{display::options{}};

	SECOND_EVENT.listener([](event::base const &base) {
		second_event const &event = static_cast<second_event const &>(base);
		std::cout << "Ticks:  " << event.ticks.rate()
				  << "\nFrames: " << event.frames.rate() << std::endl;
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
		event::queue(std::move(std::make_unique<second_event>(
			engine.tick_stats(),
			engine.frame_stats())));
	};

	engine{20.0, updater, renderer, seconder};
}
