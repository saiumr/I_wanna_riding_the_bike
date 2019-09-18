include_directories(${PROJECT_SOURCE_DIR}/test_include ../include)

macro(add_test srcfile)
    get_filename_component(src ${srcfile} NAME_WE)
    add_executable(${src}.test ${srcfile} ${ARGN})
endmacro()

add_test(ttest.c)
add_test(tlog.c ../src/log.c)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    
else()
    find_package(SDL2 REQUIRED)
endif()

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(tlog.test ${SDL2_LIBRARIES})

#TODO fix the bug
#add_custom_command(TARGET tlog.test POST_BUILD
#    COMMAND copy ${PROJECT_SOURCE_DIR}/SDL2.dll ${PROJECT_BINARY_DIR}/SDL2.dll 
#    DEPENDS ${PROJECT_SOURCE_DIR}/SDL2.dll
#)