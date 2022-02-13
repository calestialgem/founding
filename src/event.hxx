// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GECGELCEM_FOUNDING_EVENTS_HXX
#define GECGELCEM_FOUNDING_EVENTS_HXX

#include <cstddef>
#include <functional>
#include <memory>
#include <queue>
#include <vector>

namespace gecgelcem::founding::event
{
	class type;

	struct base {
		virtual type type() const noexcept = 0;
	};

	void queue(std::unique_ptr<base const> &&event) noexcept;

	void dispatch() noexcept;

	class type final
	{
		public:

		type() noexcept;

		void listener(
			std::function<void(base const &)> const listener) const noexcept;

		private:

		std::size_t const id_;

		void dispatch(base const &event) const noexcept;

		friend void dispatch() noexcept;
	};
} // namespace gecgelcem::founding::event

#endif // GECGELCEM_FOUNDING_EVENTS_HXX
