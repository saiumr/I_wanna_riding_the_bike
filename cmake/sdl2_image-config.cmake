#在这个文件下配置你的SDL2_image库的信息

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(SDL2_IMAGE_prefix ${PROJECT_SOURCE_DIR}/dependence/SDL2_image_64)
    set(SDL2_IMAGE_INCLUDE_DIRS ${SDL2_IMAGE_prefix}/include/SDL2)
    set(SDL2_IMAGE_LIBDIR ${SDL2_IMAGE_prefix}/lib)
    set(SDL2_IMAGE_LIBRARIES "-L${SDL2_IMAGE_LIBDIR} -lSDL2_image")
else()
    set(SDL2_IMAGE_INCLUDE_DIRS /usr/local/include/SDL2)
    set(SDL2_IMAGE_LIBRARIES -lSDL2_image -lSDL2 -L/usr/local/lib)
endif()
