// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "display.hxx"

#include <GL/gl.h>

int main()
{
	using namespace gecgelcem::founding::display;
	display const display{options{}};
	while (!display.is_closed()) {
		display.update();
		glClearColor(display.is_focused(), display.is_iconified(), 0.0F, 1.0F);
		display.show();
	}
}
