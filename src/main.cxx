// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include <GLFW/glfw3.h>

int main()
{
	glfwInit();
	GLFWwindow *const window =
		glfwCreateWindow(640, 480, "Founding", NULL, NULL);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}
