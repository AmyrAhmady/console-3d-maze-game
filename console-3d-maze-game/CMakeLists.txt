﻿# CMakeList.txt : CMake project for console-3d-maze-game, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
file(GLOB_RECURSE sources "*.cpp" "*.hpp")
add_executable (console-3d-maze-game ${sources})

if (UNIX)
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)
	target_link_libraries("console-3d-maze-game" Threads::Threads)
endif (UNIX)