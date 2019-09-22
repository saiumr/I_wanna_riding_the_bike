set(RESOURCES_DST ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(test)

aux_source_directory(src SRC)
add_executable(MapEditor ${SRC} ${COMMON_SRC_FILES})

#outer dependence
include_directories(${COMMON_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
#inner dependece
include_directories(include)
target_link_libraries(MapEditor ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

file(COPY ${COMMON_RESOURCES_DIRS} DESTINATION ${RESOURCES_DST})