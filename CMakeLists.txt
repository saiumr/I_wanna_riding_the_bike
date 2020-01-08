cmake_minimum_required(VERSION 3.15)
project(I_wanna_riding_the_bike)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")

set(CMAKE_CXX_FLAGS -std=c++11)
set(CMAKE_C_FLAGS -std=c99)
set(I_wanna_riding_the_bike_VERSION_MAJOR 0)
set(I_wanna_riding_the_bike_VERSION_MINOR 2)

#接下来是对工具的设置
set(USE_MapSheetor ON)  #设置使用MapSheetor

include(cmake/sdl2-config.cmake)
include(cmake/sdl2_image-config.cmake)
include(cmake/sdl2_ttf-config.cmake)
include(cmake/jsoncpp-config.cmake)
include(cmake/common-config.cmake)

include_directories(${COMMON_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

set(SDL_TOTLE_LIBRARIES ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
set(PROJECT_LINK_LIBRARIES ${COMMON_LIBRARIES} ${SDL_TOTLE_LIBRARIES})

# common库必须先包含，因为他要产生供其他文件使用的链接库
add_subdirectory(common)

add_subdirectory(tools)

link_libraries(${PROJECT_LINK_LIBRARIES})

add_subdirectory(I_wanna_riding_the_bike)
