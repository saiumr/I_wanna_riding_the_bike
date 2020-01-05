include(cmake/tool_common-config.cmake)

add_subdirectory(common)

include_directories(${TOOL_COMMON_INCLUDE_DIRS})
link_libraries(${TOOL_COMMON_LIBRARIES} ${PROJECT_LINK_LIRARIES})

add_subdirectory(ImageSheetor)
add_subdirectory(MapEditor)
