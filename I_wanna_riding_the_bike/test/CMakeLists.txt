include_directories(${PROJECT_SOURCE_DIR}/test_include ../include)

macro(add_test srcfile)
    get_filename_component(src ${srcfile} NAME_WE)
    add_executable(${src}.test ${srcfile} ${ARGN})
endmacro()

add_test(ttest.c)
add_test(tlog.c ../src/log.c)

find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    include_directories(tlog.test ${SDL2_INCLUDE_DIRS})
    target_link_libraries(tlog.test ${SDL2_LIBRARIES})
endif(SDL2_FOUND)