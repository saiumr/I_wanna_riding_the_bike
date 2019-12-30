include_directories(${COMMON_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
include_directories(../include)

#add_executable(tMapBlockActions.test tMapBlockActions.c ${COMMON_SRC_FILES} ../src/MapBlock.c ../src/MapBlockActions.c)
#target_link_libraries(tMapBlock.test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
#target_link_libraries(tMapBlockActions.test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
#TODO 在这里加上你想要的测试

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
#    add_custom_command(TARGET tbutton.test POST_BUILD
#        COMMAND cp ${SDL2_DLL_PATH} ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll
#        DEPENDS ${SDL2_DLL_PATH}
#    )
endif()

file(COPY ../resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
