// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "display.hxx"

#include <sstream>
#include <stdexcept>

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

	void options::set_context() const noexcept
	{
		glfwSwapInterval(swapInterval);
		glViewport(0, 0, width, height);
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

		glfwSetErrorCallback([](int const code, char const *const message) {
			std::stringstream error_text;
			error_text << "GLFW Error " << std::hex << code << ": " << message;
			throw std::runtime_error{error_text.str()};
		});
	}

	display::display(options const options)
		: options_{options}
	{
		init_glfw();
		monitor_ = glfwGetPrimaryMonitor();

		options_.set_hints();
		window_ = options_.create(monitor_);
		if (!window_) {
			throw std::runtime_error{"Could not create the window!"};
		}

		GLFWvidmode const *vidmode = glfwGetVideoMode(monitor_);
		glfwSetWindowPos(
			window_,
			(vidmode->width - options_.width) / 2,
			(vidmode->height - options_.height) / 2);
		glfwSetCursorPos(window_, options_.width / 2.0, options_.height / 2.0);

		set_callbacks();
		glfwMakeContextCurrent(window_);
		if (!gladLoadGL(&glfwGetProcAddress)) {
			throw std::runtime_error{"Could not initialize GL context!"};
		}
		options_.set_context();
	}

	display::~display() noexcept
	{
		glfwDestroyWindow(window_);
		glfwTerminate();
	}

	static inline display &get_display(GLFWwindow *const handle)
	{
		return *static_cast<display *>(glfwGetWindowUserPointer(handle));
	}

	void display::on_window_focused(GLFWwindow *const handle, int const focused)
	{
		get_display(handle).focused_ = focused;
	}

	void
	display::on_window_iconified(GLFWwindow *const handle, int const iconified)
	{
		get_display(handle).iconified_ = iconified;
	}
} // namespace gecgelcem::founding::display
