// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GECGELCEM_FOUNDING_ACCUMULATOR_HXX
#define GECGELCEM_FOUNDING_ACCUMULATOR_HXX

namespace gecgelcem::founding
{
	template<typename Accumulator, typename Accumulated>
	concept accumulator =
		requires(Accumulator &accumulator, Accumulated const accumulated)
	{
		accumulator += accumulated;
	};
} // namespace gecgelcem::founding

#endif // GECGELCEM_FOUNDING_ACCUMULATOR_HXX
