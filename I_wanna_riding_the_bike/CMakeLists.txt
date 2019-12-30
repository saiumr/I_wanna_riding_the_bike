aux_source_directory(src SRC)
set(GAME_EXE_NAME play)
include_directories(include)

add_executable(${GAME_EXE_NAME} main.cpp ${SRC} ${COMMON_SRC})

add_subdirectory(test)
