add_subdirectory(test)

aux_source_directory(src SRC)
include_directories(include)

add_executable(MapEditor ${SRC})
