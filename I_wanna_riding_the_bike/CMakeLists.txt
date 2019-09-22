add_subdirectory("test")
aux_source_directory(src SRC)

set(GAME_EXE_NAME play)
set(RESOURCES_SRC ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(RESOURCES_DST ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${GAME_EXE_NAME} ${SRC} ${COMMON_SRC_FILES})

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_custom_command(TARGET ${GAME_EXE_NAME} POST_BUILD
        COMMAND cp ${SDL2_DLL_PATH} ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll
        DEPENDS ${SDL2_DLL_PATH}
    )   
    #file(COPY ${SDL2_DLL_PATH} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) #如果上面的不行，就试试这个
endif()

#copy sources to build folder
file(COPY ${RESOURCES_SRC} DESTINATION ${RESOURCES_DST})
file(COPY ${COMMON_RESOURCES_DIRS} DESTINATION ${RESOURCES_DST})

#usr's include files
include_directories(./include ${COMMON_INCLUDE_DIRS})
#SDL2 include files
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(${GAME_EXE_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})