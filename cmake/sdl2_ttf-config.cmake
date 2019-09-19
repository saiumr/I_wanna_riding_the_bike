#在这个文件下配置你的SDL2_ttf库的信息

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    #TODO 编写windows下的SDL2_ttf库和头文件的搜索路径
else()
    set(SDL2_TTF_INCLUDE_DIRS /usr/local/include/SDL2)
    set(SDL2_TTF_LIBRARIES -lSDL2_ttf -lSDL2 -L/usr/local/lib)
endif()