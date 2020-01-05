include_directories(include)
aux_source_directory(src SRC)
aux_source_directory(src/engin ENGIN)

link_libraries(${PROJECT_LINK_LIBRARIES})

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(${COMMON_LIBRARY_NAME} STATIC ${SRC} ${ENGIN})

add_subdirectory(GUITestframe)

add_subdirectory(test)