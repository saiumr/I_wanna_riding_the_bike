include(cmake/tool_common-config.cmake)

add_subdirectory(common)

include_directories(${TOOL_COMMON_INCLUDE_DIRS})
link_libraries(${TOOL_COMMON_LIBRARIES} ${COMMON_PURE_LIBRARIES} ${SDL_TOTLE_LIBRARIES})

add_subdirectory(ImageSheetor)
add_subdirectory(MapEditor)
