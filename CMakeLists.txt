cmake_minimum_required(VERSION 3.10)
project(I_wanna_riding_the_bike)
set(I_wanna_riding_the_bike_VERSION_MAJOR 0)
set(I_wanna_riding_the_bike_VERSION_MINOR 1)

set(SDL2_DLL_PATH ${PROJECT_SOURCE_DIR}\\dependence\\SDL2_64\\bin\\SDL2.dll)

include(cmake/sdl2-config.cmake)
include(cmake/sdl2_image-config.cmake)
include(FindPkgConfig)

add_subdirectory("tools")
add_subdirectory("I_wanna_riding_the_bike")