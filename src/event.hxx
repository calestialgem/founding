// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GECGELCEM_FOUNDING_EVENTS_HXX
#define GECGELCEM_FOUNDING_EVENTS_HXX

#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <vector>

namespace gecgelcem::founding::event
{
	enum type
	{
		DEBUG
	};

	struct event {
		virtual type type() const noexcept = 0;
	};

	struct debug_event : event {
		std::string message;

		debug_event(std::string message)
			: message(message)
		{
		}

		enum type type() const noexcept override
		{
			return type::DEBUG;
		}
	};

	class dispatcher final
	{
		public:

		inline void dispatch(std::unique_ptr<event const> &&event) noexcept
		{
			queue_.emplace(std::move(event));
		}

		inline void register_listener(
			type                               type,
			std::function<void(event const &)> listener) noexcept
		{
			listeners_[type].push_back(listener);
		}

		inline void dispatch_all() noexcept
		{
			while (!queue_.empty()) {
				auto &event = queue_.front();
				for (auto const &listener : listeners_[event->type()]) {
					listener(*event);
				}
				queue_.pop();
			}
		}

		private:

		std::queue<std::unique_ptr<event const>> queue_;
		std::map<type, std::vector<std::function<void(event const &)>>>
			listeners_;
	};
} // namespace gecgelcem::founding::event

#endif // GECGELCEM_FOUNDING_EVENTS_HXX
