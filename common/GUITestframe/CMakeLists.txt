set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
include_directories(include)
aux_source_directory(src GUI_TESTFRAMEWORK_SRC)
add_library(${COMMON_TEST_LIB_NAME} STATIC ${GUI_TESTFRAMEWORK_SRC})

#TODO 当链接库更新的时候程序没有自动更新