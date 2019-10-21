macro(add_test srcfile)
    get_filename_component(src ${srcfile} NAME_WE)
    add_executable(${src}.test ${srcfile} ${ARGN})
endmacro()

set(SRCDIR ../src)

add_test(ttest.c)
add_test(tlog.c ${COMMON_SRC_DIRS}/log.c)
add_test(tLinkList.c ${COMMON_SRC_DIRS}/linklist.c)
add_test(tmmath.c ${COMMON_SRC_DIRS}/mmath.c)
add_test(tSDL_Draw.c ${COMMON_SRC_DIRS}/SDL_Draw.c ${COMMON_SRC_DIRS}/mmath.c)
add_test(tparticalSystemGUI.c ${COMMON_SRC_DIRS}/SDL_Draw.c ${COMMON_SRC_DIRS}/mmath.c ${SRCDIR}/particalSystem.c)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_custom_command(TARGET tlog.test POST_BUILD
        COMMAND cp ${SDL2_DLL_PATH} ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll
        DEPENDS ${SDL2_DLL_PATH}
    )
    #file(COPY ${SDL2_DLL_PATH} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) #如果上面的不行，就试试这个
endif()

include_directories(${PROJECT_SOURCE_DIR}/test_include ${COMMON_INCLUDE_DIRS} ../include)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(tlog.test ${SDL2_LIBRARIES})
target_link_libraries(tmmath.test ${SDL2_LIBRARIES})
target_link_libraries(tSDL_Draw.test ${SDL2_LIBRARIES})
target_link_libraries(tparticalSystemGUI.test ${SDL2_LIBRARIES})