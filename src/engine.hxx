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
					profiler profiler{tick_counter_};
					updater(*this);
					--ticks_waiting_;
				}

				if (rendering_) {
					profiler profiler{frame_counter_};
					renderer(*this);
				}

				if (seconds >= 1.0) {
					seconds          = seconds + 1.0;
					ticks_snapshot_  = tick_counter_;
					frames_snapshot_ = frame_counter_;
					tick_counter_.refresh();
					frame_counter_.refresh();
					seconder(*this);
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
			return ticks_snapshot_;
		}

		constexpr statistics const &frame_stats() const noexcept
		{
			return frames_snapshot_;
		}

		private:

		bool   running_{true};
		bool   rendering_{true};
		double ticks_waiting_{0.0};

		statistics tick_counter_;
		statistics frame_counter_;
		statistics ticks_snapshot_;
		statistics frames_snapshot_;
	};
} // namespace gecgelcem::founding

#endif // GECGELCEM_FOUNDING_ENGINE_HXX
