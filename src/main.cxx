// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "display.hxx"
#include "engine.hxx"
#include "event.hxx"

#include <cstddef>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using namespace gecgelcem::founding;

static event::type const SECOND_EVENT{};
static event::type const MESSAGE_EVENT{};

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

	void print(std::ostream &out) const noexcept override
	{
		out << "Ticks: " << ticks.rate() << " Frames: " << frames.rate();
	}
};

struct message_event : event::base {
	std::string message;

	message_event(std::string message)
		: message{message}
	{
	}

	event::type type() const noexcept override
	{
		return MESSAGE_EVENT;
	}

	void print(std::ostream &out) const noexcept override
	{
		out << message;
	}
};

template<unsigned int const Message>
static void on_second_event(event::base const &base)
{
	second_event const &event = static_cast<second_event const &>(base);
	std::stringstream   builder{};
	builder << "[MESSAGE " << Message << "] @" << event.ticks.count();
	event::queue(std::make_unique<message_event>(builder.str()));
}

int main()
{
	display::display const display{display::options{}};

	SECOND_EVENT.listener(&on_second_event<0U>);
	SECOND_EVENT.listener(&on_second_event<1U>);
	SECOND_EVENT.listener(&on_second_event<2U>);
	SECOND_EVENT.listener(&on_second_event<3U>);

	MESSAGE_EVENT.listener([](event::base const &base) {
		message_event const &event = static_cast<message_event const &>(base);
		std::cout << event.message << std::endl;
	});

	auto const updater = [&display](engine &engine) {
		display.update();
		event::dispatch(engine.tick_stats().count());
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
