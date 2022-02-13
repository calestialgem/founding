// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "event.hxx"

#include <cstddef>

namespace gecgelcem::founding::event
{
	static std::queue<std::unique_ptr<base const>> waiting;
	static std::vector<std::vector<std::function<void(base const &)>>>
		listeners;

	void queue(std::unique_ptr<base const> &&event) noexcept
	{
		waiting.emplace(std::move(event));
	}

	void dispatch() noexcept
	{
		while (!waiting.empty()) {
			auto const &event = waiting.front();
			event->type().dispatch(*event);
			waiting.pop();
		}
	}

	type::type() noexcept
		: id_{listeners.size()}
	{
		listeners.emplace_back(
			std::move(std::vector<std::function<void(base const &)>>()));
	}

	void type::listener(
		std::function<void(base const &)> const listener) const noexcept
	{
		listeners[id_].push_back(listener);
	}

	void type::dispatch(base const &event) const noexcept
	{
		for (auto const &listener : listeners[id_]) {
			listener(event);
		}
	}
} // namespace gecgelcem::founding::event
