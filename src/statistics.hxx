// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GECGELCEM_FOUNDING_STATISTICS_HXX
#define GECGELCEM_FOUNDING_STATISTICS_HXX

namespace gecgelcem::founding
{
	class statistics final
	{
		public:

		constexpr statistics &operator+=(double const duration) noexcept
		{
			total_time_ += duration;
			++counter_;
			++interval_counter_;
			return *this;
		}

		constexpr void refresh() noexcept
		{
			interval_counter_ = 0U;
		}

		constexpr double average() const noexcept
		{
			return total_time_ / counter_;
		}

		constexpr unsigned long long count() const noexcept
		{
			return counter_;
		}

		constexpr unsigned int rate() const noexcept
		{
			return interval_counter_;
		}

		private:

		double             total_time_{0.0};
		unsigned long long counter_{0UL};
		unsigned int       interval_counter_{0U};
	};
} // namespace gecgelcem::founding

#endif // GECGELCEM_FOUNDING_STATISTICS_HXX
