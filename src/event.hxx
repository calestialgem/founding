// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GECGELCEM_FOUNDING_EVENTS_HXX
#define GECGELCEM_FOUNDING_EVENTS_HXX

#include <functional>
#include <memory>
#include <ostream>
#include <spdlog/fmt/bundled/core.h>
#include <string>

namespace gecgelcem::founding::event
{
	class type;

	struct base {
		virtual type type() const noexcept = 0;

		virtual fmt::appender
		format(fmt::format_context &ctx) const noexcept = 0;
	};

	void queue(std::unique_ptr<base const> &&event) noexcept;

	void dispatch(unsigned long long const tick) noexcept;

	class type final
	{
		public:

		type() noexcept;

		void listener(
			std::function<void(base const &)> const listener) const noexcept;

		private:

		std::size_t id_;

		void dispatch(base const &event, unsigned long long const tick)
			const noexcept;

		friend void dispatch(unsigned long long const tick) noexcept;
	};
} // namespace gecgelcem::founding::event

template<>
struct fmt::formatter<gecgelcem::founding::event::base> {
	constexpr auto parse(format_parse_context &ctx)
	{
		return ctx.begin();
	}

	constexpr auto
	format(gecgelcem::founding::event::base const &base, format_context &ctx)
	{
		return base.format(ctx);
	}
};

#endif // GECGELCEM_FOUNDING_EVENTS_HXX
