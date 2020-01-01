aux_source_directory(src SRC)
include_directories(include)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(tool_common STATIC ${SRC})
