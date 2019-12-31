cmake_minimum_required(VERSION 3.10)
project(I_wanna_riding_the_bike)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")

set(CMAKE_CXX_FLAGS -std=c++11)
set(CMAKE_C_FLAGS -std=c99)
set(I_wanna_riding_the_bike_VERSION_MAJOR 0)
set(I_wanna_riding_the_bike_VERSION_MINOR 2)

include(cmake/sdl2-config.cmake)
include(cmake/sdl2_image-config.cmake)
include(cmake/sdl2_ttf-config.cmake)
include(cmake/jsoncpp-config.cmake)
include(cmake/common-config.cmake)

macro(Add_Test testname)
    aux_source_directory(../src source_files)
    add_executable(${testname}_test ${testname}.cpp ${source_files})
endmacro()

link_libraries(${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${JsonCpp_LIBRARIES})
include_directories(${COMMON_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${JsonCpp_INCLUDE_DIRS})

# common库必须先包含，因为他要产生供其他文件使用的链接库
add_subdirectory(common)

link_libraries(${COMMON_LIBRARIES})

add_subdirectory(I_wanna_riding_the_bike)
add_subdirectory(tools)
