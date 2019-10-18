cmake_minimum_required(VERSION 3.10)
project(I_wanna_riding_the_bike)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_compile_options(-std=c99)
set(I_wanna_riding_the_bike_VERSION_MAJOR 0)
set(I_wanna_riding_the_bike_VERSION_MINOR 1)

set(SDL2_DLL_PATH ${PROJECT_SOURCE_DIR}/dependence/SDL2_64/bin/SDL2.dll)
set(SDL2_IMAGE_DLL_PATH ${PROJECT_SOURCE_DIR}/dependence/SDL2_image_64/bin/SDL2_image.dll)

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