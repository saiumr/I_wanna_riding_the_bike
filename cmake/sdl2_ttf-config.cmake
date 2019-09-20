#在这个文件下配置你的SDL2_ttf库的信息

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    #TODO 在Windows下测试是否可以找到这个库
    set(SDL2_TTF_prefix ${PROJECT_SOURCE_DIR}/dependence/SDL2_ttf_64)
    set(SDL2_TTF_INCLUDE_DIRS ${SDL2_TTF_prefix}/include/SDL2)
    set(SDL2_TTF_LIBDIR ${SDL2_TTF_prefix}/lib)
    set(SDL2_TTF_LIBRARIES "-L${SDL2_TTF_LIBDIR} -lSDL2_ttf")
else()
    set(SDL2_TTF_INCLUDE_DIRS /usr/local/include/SDL2)
    set(SDL2_TTF_LIBRARIES "-lSDL2_ttf -lSDL2 -L/usr/local/lib")
endif()