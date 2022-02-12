// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "display.hxx"

#include "GLFW/glfw3.h"

namespace gecgelcem::founding::display
{
	void options::set_hints() const noexcept
	{
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_RESIZABLE, false);
		glfwWindowHint(GLFW_DECORATED, decorated);
		glfwWindowHint(GLFW_SAMPLES, samples);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifndef NDEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
	}

	GLFWwindow *options::create(GLFWmonitor *const monitor) const noexcept
	{
		return glfwCreateWindow(
			width,
			height,
			title.c_str(),
			fullscreen ? monitor : NULL,
			NULL);
	}

	static void init_glfw()
	{
		static bool initialized = false;
		if (initialized) {
			return;
		}
		initialized = true;

		if (!glfwInit()) {
			throw std::runtime_error{
				"Could not initialize the GLFW Window Library!"};
		}

		glfwSetErrorCallback([](int code, char const *message) {
			std::stringstream error_text;
			error_text << "GLFW Error " << std::hex << code << ": " << message;
			throw std::runtime_error{error_text.str()};
		});
	}

	display::display(struct options options)
		: options_{options}
	{
		init_glfw();
		monitor_ = glfwGetPrimaryMonitor();
		options.set_hints();
		window_ = options.create(monitor_);
		if (!window_) {
			throw std::runtime_error{"Could not create the window!"};
		}
		glfwSetWindowUserPointer(window_, this);
	}

	display::~display() noexcept
	{
		glfwDestroyWindow(window_);
		glfwTerminate();
	}
} // namespace gecgelcem::founding::display
