include_directories(include)
aux_source_directory(src SRC)
aux_source_directory(src/engin ENGIN)
aux_source_directory(src/engin/gui GUI)
aux_source_directory(src/engin/filesystem FILESYSTEM)

link_libraries(${COMMON_PURE_LIBRARIES} ${SDL_TOTLE_LIBRARIES})

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(${COMMON_LIBRARY_NAME} STATIC ${SRC} ${ENGIN} ${GUI} ${FILESYSTEM})

add_subdirectory(GUITestframe)

add_subdirectory(test)