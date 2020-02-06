include_directories(${COMMON_PURE_INCLUDE_DIRS} ${COMMON_TEST_INCLUDE_DIRS})
link_libraries(${COMMON_PURE_LIBRARIES} ${SDL_TOTLE_LIBRARIES})

add_executable(functions_test functions.cpp)
add_executable(mmath_test mmath.cpp)
add_executable(SDL_Draw_test SDL_Draw.cpp)
add_executable(test_test test.cpp)
add_executable(RectRectCollision_test RectRectCollision.cpp)
add_executable(GUI_Components_test GUI_Components.cpp)
add_executable(Animation_test Animation.cpp)

target_link_libraries(RectRectCollision_test ${COMMON_TEST_LIBRARIES})
target_link_libraries(GUI_Components_test ${COMMON_TEST_LIBRARIES})
target_link_libraries(Animation_test ${COMMON_TEST_LIBRARIES})
