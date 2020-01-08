include_directories(include)
aux_source_directory(src SRC)
aux_source_directory(src/engin ENGIN)
aux_source_directory(src/engin/gui GUI)

link_libraries(${COMMON_PURE_LIBRARIES} ${SDL_TOTLE_LIBRARIES})

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(${COMMON_LIBRARY_NAME} STATIC ${SRC} ${ENGIN} ${GUI})

add_subdirectory(GUITestframe)

add_subdirectory(test)