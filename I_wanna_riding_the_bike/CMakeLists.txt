add_subdirectory("test")
aux_source_directory(src SRC)

set(GAME_EXE_NAME play)


add_executable(${GAME_EXE_NAME} ${SRC})

include_directories(./include)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    
else()
    find_package(SDL2 REQUIRED)
endif()

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${GAME_EXE_NAME} ${SDL2_LIBRARIES})
