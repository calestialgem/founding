// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "display.hxx"

int main()
{
	using namespace gecgelcem::founding::display;
	display display{options{}};
	while (!display.is_closed()) {
		display.update();
	}
}
