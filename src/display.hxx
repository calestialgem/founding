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
	struct options {
		int         width        = 1280;
		int         height       = 720;
		std::string title        = std::string{"Mending Engine"};
		bool        fullscreen   = false;
		bool        decorated    = true;
		int         samples      = 16;
		int         swapInterval = 1;

		private:

		void        set_hints() const noexcept;
		GLFWwindow *create(GLFWmonitor *const monitor) const noexcept;

		friend class display;
	};

	struct display {
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

		private:

		display() = delete;

		display(display const &other) = delete;
		display &operator=(display const &other) = delete;

		display(display &&other) = delete;
		display &operator=(display &&other) = delete;

		options      options_;
		GLFWmonitor *monitor_;
		GLFWwindow  *window_;
	};
} // namespace gecgelcem::founding::display

#endif // GECGELCEM_FOUNDING_DISPLAY_HXX
