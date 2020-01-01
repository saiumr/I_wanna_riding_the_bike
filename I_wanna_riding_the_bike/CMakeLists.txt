aux_source_directory(src SRC)
aux_source_directory(src/scenes SRC)
aux_source_directory(src/controllers SRC)

set(GAME_EXE_NAME play)
include_directories(include)

link_libraries(${COMMON_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

add_executable(${GAME_EXE_NAME} main.cpp ${SRC})

add_subdirectory(test)
