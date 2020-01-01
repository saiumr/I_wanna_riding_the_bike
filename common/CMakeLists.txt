include_directories(include)
aux_source_directory(src SRC)
aux_source_directory(src/engin ENGIN)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(${COMMON_LIBRARY_NAME} STATIC ${SRC} ${ENGIN})

link_libraries(${COMMON_LIBRARIES})

add_subdirectory(test)