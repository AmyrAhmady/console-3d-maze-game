# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

add_definitions(-DUNICODE -D_UNICODE)
set (CMAKE_CXX_STANDARD 11)
project ("console-3d-maze-game")

# Include sub-projects.
add_subdirectory ("console-3d-maze-game")

