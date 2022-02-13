// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GECGELCEM_FOUNDING_ENGINE_HXX
#define GECGELCEM_FOUNDING_ENGINE_HXX

#include "profiler.hxx"
#include "statistics.hxx"
#include "timer.hxx"

namespace gecgelcem::founding
{
	class engine final
	{
		public:

		template<typename Updater, typename Renderer, typename Seconder>
		inline engine(
			double const    target_tick_rate,
			Updater const  &updater,
			Renderer const &renderer,
			Seconder const &seconder) noexcept
		{
			timer iterations;
			timer seconds;
			while (running_) {
				ticks_waiting_ += iterations.elapsed() * target_tick_rate;
				iterations = timer{};

				while (ticks_waiting_ >= 1.0) {
					profiler profiler{ticks_};
					updater(*this);
					--ticks_waiting_;
				}

				if (rendering_) {
					profiler profiler{frames_};
					renderer(*this);
				}

				if (seconds >= 1.0) {
					seconds = seconds + 1.0;
					seconder(*this);
					ticks_.refresh();
					frames_.refresh();
				}
			}
		}

		constexpr void close() noexcept
		{
			running_ = false;
		}

		constexpr void enable_rendering(bool const rendering) noexcept
		{
			rendering_ = rendering;
		}

		constexpr statistics const &tick_stats() const noexcept
		{
			return ticks_;
		}

		constexpr statistics const &frame_stats() const noexcept
		{
			return frames_;
		}

		private:

		bool   running_{true};
		bool   rendering_{true};
		double ticks_waiting_{0.0};

		statistics ticks_;
		statistics frames_;
	};
} // namespace gecgelcem::founding

#endif // GECGELCEM_FOUNDING_ENGINE_HXX
