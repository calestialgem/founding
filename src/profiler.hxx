// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GECGELCEM_FOUNDING_PROFILER_HXX
#define GECGELCEM_FOUNDING_PROFILER_HXX

#include "accumulator.hxx"
#include "timer.hxx"

namespace gecgelcem::founding
{
	template<accumulator<double> Accumulator>
	class profiler final
	{
		public:

		inline profiler(Accumulator &accumulator) noexcept
			: accumulator(accumulator)
		{
		}

		inline ~profiler() noexcept
		{
			accumulator += timer.elapsed();
		}

		private:

		Accumulator &accumulator;
		timer        timer;
	};
} // namespace gecgelcem::founding

#endif // GECGELCEM_FOUNDING_PROFILER_HXX
