aux_source_directory(src SRC)
aux_source_directory(src/scenes SCENES)
aux_source_directory(src/controllers CONTROLLERS)
set(GAME_EXE_NAME play)
include_directories(include)

add_executable(${GAME_EXE_NAME} main.cpp ${SRC} ${CONTROLLERS} ${SCENES} ${COMMON_SRC})

add_subdirectory(test)
