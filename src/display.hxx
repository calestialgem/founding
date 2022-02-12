// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef GECGELCEM_FOUNDING_DISPLAY_HXX
#define GECGELCEM_FOUNDING_DISPLAY_HXX

#include "GLFW/glfw3.h"

#include <GL/gl.h>
#include <sstream>
#include <stdexcept>
#include <string>

namespace gecgelcem::founding::display
{
	struct options final {
		int         width{1280};
		int         height{720};
		std::string title{"Founding II"};
		bool        fullscreen{false};
		bool        decorated{true};
		int         samples{16};
		int         swapInterval{1};

		private:

		void        set_hints() const noexcept;
		GLFWwindow *create(GLFWmonitor *const monitor) const noexcept;
		void        set_context() const noexcept;

		friend class display;
	};

	struct display final {
		display(struct options options);
		~display() noexcept;

		inline void show() const noexcept
		{
			glfwSwapBuffers(window_);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		inline void update() const noexcept
		{
			glfwPollEvents();
		}

		inline bool is_closed() const noexcept
		{
			return glfwWindowShouldClose(window_);
		}

		inline bool is_focused() const noexcept
		{
			return focused_;
		}

		inline bool is_iconified() const noexcept
		{
			return iconified_;
		}

		private:

		display() = delete;

		display(display const &other) = delete;
		display &operator=(display const &other) = delete;

		display(display &&other) = delete;
		display &operator=(display &&other) = delete;

		inline void set_callbacks() noexcept
		{
			glfwSetWindowUserPointer(window_, this);
			glfwSetWindowFocusCallback(window_, &on_window_focused);
			glfwSetWindowIconifyCallback(window_, &on_window_iconified);
		}

		static void
		on_window_focused(GLFWwindow *const handle, int const focused);
		static void
		on_window_iconified(GLFWwindow *const handle, int const iconified);

		options      options_;
		GLFWmonitor *monitor_{nullptr};
		GLFWwindow  *window_{nullptr};
		bool         focused_{true};
		bool         iconified_{false};
	};
} // namespace gecgelcem::founding::display

#endif // GECGELCEM_FOUNDING_DISPLAY_HXX
