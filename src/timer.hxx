// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GECGELCEM_FOUNDING_TIMER_HXX
#define GECGELCEM_FOUNDING_TIMER_HXX

#include "opengl.hxx"

#include <compare>

namespace gecgelcem::founding
{
	class timer final
	{
		public:

		static inline double time() noexcept
		{
			return glfwGetTime();
		}

		inline timer() {}

		inline double elapsed() const noexcept
		{
			return timer{} - *this;
		}

		constexpr auto operator<=>(timer const &other) const noexcept = default;

		inline auto operator<=>(double const duration) const noexcept
		{
			return elapsed() <=> duration;
		};

		constexpr timer operator+(double const duration) const noexcept
		{
			return timer{start_ + duration};
		}

		constexpr double operator-(timer const &other) const noexcept
		{
			return start_ - other.start_;
		}

		private:

		double start_{time()};

		constexpr timer(double const start) noexcept
			: start_{start}
		{
		}
	};
} // namespace gecgelcem::founding

#endif // GECGELCEM_FOUNDING_TIMER_HXX
