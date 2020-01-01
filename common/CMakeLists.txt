include_directories(include)
aux_source_directory(src SRC)
aux_source_directory(src/engin ENGIN)

link_libraries(${COMMON_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(${COMMON_LIBRARY_NAME} STATIC ${SRC} ${ENGIN})

add_subdirectory(test)