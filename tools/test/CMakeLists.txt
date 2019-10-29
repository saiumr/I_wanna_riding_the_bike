include_directories(${COMMON_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
include_directories(../include)

#list(APPEND ${SRC} ${COMMON_SRC_FILES} ../src/UI.c)

#add_executable(tbutton.test ${SRC} ${COMMON_SRC_DIRS}/SDL_FontCache.c ../src/UI.c)
#add_executable(tbutton.test tbutton.c ${COMMON_SRC_FILES} ../src/UI.c)
#add_executable(timage.test timage.c ${COMMON_SRC_FILES} ../src/UI.c)
#add_executable(tLinkList.test tLinkList.c ${COMMON_SRC_FILES} ../src/UI.c)
add_executable(tMapBlock.test tMapBlock.c ${COMMON_SRC_FILES} ../src/MapBlock.c)
add_executable(tMapBlockActions.test tMapBlockActions.c ${COMMON_SRC_FILES} ../src/MapBlock.c ../src/MapBlockActions.c)
#target_link_libraries(tbutton.test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
#target_link_libraries(timage.test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
#target_link_libraries(tLinkList.test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_link_libraries(tMapBlock.test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_link_libraries(tMapBlockActions.test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_custom_command(TARGET tbutton.test POST_BUILD
        COMMAND cp ${SDL2_DLL_PATH} ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll
        DEPENDS ${SDL2_DLL_PATH}
    )
endif()

file(COPY ../resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

copy_common_resources()