include_directories(include)
aux_source_directory(src SRC)
aux_source_directory(src/engin ENGIN)
aux_source_directory(src/engin/gui GUI)
#aux_source_directory(src/engin/filesystem FILESYSTEM)
aux_source_directory(src/engin/action ACTION)

link_libraries(${COMMON_PURE_LIBRARIES} ${SDL_TOTLE_LIBRARIES})

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(${COMMON_LIBRARY_NAME} STATIC ${SRC} ${ENGIN} ${GUI} ${FILESYSTEM} ${ACTION})

add_subdirectory(GUITestframe)

add_subdirectory(test)