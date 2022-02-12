// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "display.hxx"
#include "engine.hxx"

#include <GL/gl.h>
#include <iostream>

int main()
{
	using namespace gecgelcem::founding;
	display::display const display{display::options{}};

	auto const updater = [&display](engine &engine) {
		display.update();
		engine.enable_rendering(display.is_focused());
		if (display.is_closed()) {
			engine.close();
		}
	};

	auto const renderer = [&display](engine &engine) {
		glClearColor(
			display.is_focused(),
			display.is_iconified(),
			display.is_closed(),
			1.0);
		display.show();
	};

	auto const seconder = [](engine &engine) {
		std::cout << "Ticks:  " << engine.tick_stats().rate()
				  << "\nFrames: " << engine.frame_stats().rate() << std::endl;
	};

	engine{20.0, updater, renderer, seconder};
}
