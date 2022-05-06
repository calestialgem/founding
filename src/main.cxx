// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "display.hxx"
#include "engine.hxx"
#include "event.hxx"
#include "spdlog/common.h"
#include "spdlog/details/log_msg.h"

#include <cstddef>
#include <iostream>
#include <memory>
#include <spdlog/fmt/bundled/core.h>
#include <spdlog/pattern_formatter.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include <utility>

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

	fmt::appender format(fmt::format_context &ctx) const noexcept override
	{
		return fmt::format_to(
			ctx.out(),
			"Ticks: {} Frames: {}",
			ticks.rate(),
			frames.rate());
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

	fmt::appender format(fmt::format_context &ctx) const noexcept override
	{
		return fmt::format_to(ctx.out(), "{}", message);
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

class tick_formatter_flag final : public spdlog::custom_flag_formatter
{
	public:

	tick_formatter_flag(engine const &engine)
		: engine(engine)
	{
	}

	void format(
		spdlog::details::log_msg const &,
		std::tm const &,
		spdlog::memory_buf_t &dest) override
	{
		auto builder = std::stringstream{};
		builder << engine.tick_stats().count();
		auto const text = builder.str();
		dest.append(text.data(), text.data() + text.size());
	}

	std::unique_ptr<spdlog::custom_flag_formatter> clone() const override
	{
		return spdlog::details::make_unique<tick_formatter_flag>(engine);
	}

	private:

	engine const &engine;
};

int main()
{
	display::display const display{display::options{}};

	SECOND_EVENT.listener(&on_second_event<0U>);
	SECOND_EVENT.listener(&on_second_event<1U>);
	SECOND_EVENT.listener(&on_second_event<2U>);
	SECOND_EVENT.listener(&on_second_event<3U>);

	MESSAGE_EVENT.listener([](event::base const &base) {
		message_event const &event = static_cast<message_event const &>(base);
		SPDLOG_INFO("{}", event.message);
	});

	auto const initilizer = [](engine &engine) {
		auto formatter = std::make_unique<spdlog::pattern_formatter>();
		formatter->add_flag<tick_formatter_flag>('*', engine)
			.set_pattern("%C.%m.%d.%H.%M.%S @%* %s:%# > %^[%=8l]%$: %v");
		spdlog::set_formatter(std::move(formatter));
	};

	auto const updater = [&display](engine &engine) {
		display.update();
		event::dispatch(engine.tick_stats().count());
		engine.enable_rendering(display.is_focused());
		if (display.is_closed()) {
			engine.close();
		}
	};

	auto const renderer = [&display](engine &) {
		glClearColor(
			display.is_focused(),
			display.is_iconified(),
			display.is_closed(),
			1.0);
		display.show();
	};

	auto const seconder = [](engine &engine) {
		event::queue(std::make_unique<second_event>(
			engine.tick_stats(),
			engine.frame_stats()));
	};

	engine{20.0, initilizer, updater, renderer, seconder};
}
