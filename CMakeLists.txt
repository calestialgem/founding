# SPDX-FileCopyrightText: (C) 2022 Cem Geçgel <gecgelcem@outlook.com>
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.21.2)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(founding)
add_executable(${PROJECT_NAME}
src/main.cxx
src/display.hxx
src/display.cxx
src/accumulator.hxx
src/timer.hxx
src/profiler.hxx
src/statistics.hxx
src/engine.hxx
src/event.hxx
src/event.cxx
)

# Warnings
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /Wall)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL)

# GLFW
target_include_directories(${PROJECT_NAME} PUBLIC glfw/include)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

# GLAD
add_subdirectory(glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)

# SPDLOG
add_subdirectory(spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
