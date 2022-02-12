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
		if (display.is_closed()) {
			engine.close();
		}
	};

	auto const renderer = [&display](engine &engine) {
		display.show();
	};

	auto const seconder = [](engine &engine) {
		std::cout << "Ticks:  " << engine.tick_stats().rate()
				  << "\nFrames: " << engine.frame_stats().rate() << std::endl;
	};

	engine{20.0, updater, renderer, seconder};

	while (!display.is_closed()) {
		display.update();
		glClearColor(display.is_focused(), display.is_iconified(), 0.0F, 1.0F);
		display.show();
	}
}
