include_directories(${PROJECT_SOURCE_DIR}/test_include ../include)

macro(add_test srcfile)
    get_filename_component(src ${srcfile} NAME_WE)
    add_executable(${src}.test ${srcfile} ${ARGN})
endmacro()

add_test(ttest.c)
add_test(tlog.c ../src/log.c)

if(NOT CMAKE_SYSTEM_NAME MATCHES "Windows")
    find_package(SDL2 REQUIRED)
else()
    add_custom_command(TARGET tlog.test POST_BUILD
        COMMAND cp ${SDL2_DLL_PATH} ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll
        DEPENDS ${SDL2_DLL_PATH}
    )
    #file(COPY ${SDL2_DLL_PATH} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) #如果上面的不行，就试试这个
endif()

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(tlog.test ${SDL2_LIBRARIES})