include_directories(${PROJECT_SOURCE_DIR}/test_include ../include)

macro(add_test srcfile)
    get_filename_component(src ${srcfile} NAME_WE)
    add_executable(${src}.test ${srcfile} ${ARGN})
endmacro()

add_test(ttest.c)
add_test(tlog.c ../src/log.c)