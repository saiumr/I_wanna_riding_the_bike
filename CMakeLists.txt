cmake_minimum_required(VERSION 3.10)
project(I_wanna_riding_the_bike)

add_definitions("-Wall -g")
SET(CMAKE_BUILD_TYPE "Debug")

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_compile_options(-std=c99)
set(I_wanna_riding_the_bike_VERSION_MAJOR 0)
set(I_wanna_riding_the_bike_VERSION_MINOR 1)

macro(copy_common_resources)
    file(COPY ${COMMON_RESOURCES_DIRS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endmacro()

#SDL2 and own libs
include(cmake/sdl2-config.cmake)
include(cmake/sdl2_image-config.cmake)
include(cmake/sdl2_ttf-config.cmake)
include(cmake/common-config.cmake)

add_subdirectory("tools")
add_subdirectory("I_wanna_riding_the_bike")