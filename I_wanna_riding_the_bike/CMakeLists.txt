aux_source_directory(src SRC)
aux_source_directory(src/scenes SRC)
aux_source_directory(src/controllers SRC)

set(GAME_EXE_NAME play)
include_directories(include)


link_libraries(${PROJECT_LINK_LIBRARIES})

add_executable(${GAME_EXE_NAME} main.cpp ${SRC} ${CONTROLLERS} ${SCENES})

add_subdirectory(test)
