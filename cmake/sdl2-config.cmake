# sdl2 cmake project-config input for ./configure scripts

if(NOT CMAKE_SYSTEM_NAME MATCHES "Windows")
    find_package(SDL2 REQUIRED)
else()
    set(prefix "${PROJECT_SOURCE_DIR}/dependence/SDL-2.0") 
    set(exec_prefix "${prefix}")
    set(libdir "${exec_prefix}/lib")
    set(SDL2_LIBDIR "${exec_prefix}/lib")
    set(SDL2_INCLUDE_DIRS "${prefix}/include/SDL2")
    set(SDL2_LIBRARIES "-L${SDL2_LIBDIR}  -lmingw32 -lSDL2main -lSDL2 -mwindows")
    #set(SDL2_DLL_PATH ${prefix}/bin)
    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
endif()
