// SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

/** This file makes sure that OpenGL system headers are included in the correct
 * order. */
#ifndef GECGELCEM_FOUNDING_OPENGL_HXX
#define GECGELCEM_FOUNDING_OPENGL_HXX

#include <glad/gl.h>

// After glad; or you can use GLFW_INCLUDE_NONE and include glfw before glad.

#include <GLFW/glfw3.h>

#endif // GECGELCEM_FOUNDING_OPENGL_HXX
