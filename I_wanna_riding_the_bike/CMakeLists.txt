add_subdirectory("test")
aux_source_directory(src SRC)

set(GAME_EXE_NAME play)
set(SOURCES_SRC ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(SOURCES_DST ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${GAME_EXE_NAME} ${SRC})

include_directories(./include)

if(NOT CMAKE_SYSTEM_NAME MATCHES "Windows")
    find_package(SDL2 REQUIRED)
else()
    add_custom_command(TARGET ${GAME_EXE_NAME} POST_BUILD
        COMMAND cp ${SDL2_DLL_PATH} ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll
        DEPENDS ${SDL2_DLL_PATH}
    )   
    #file(COPY ${SDL2_DLL_PATH} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) #如果上面的不行，就试试这个
endif()

file(COPY ${SOURCES_SRC} DESTINATION ${SOURCES_DST})

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(${GAME_EXE_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})