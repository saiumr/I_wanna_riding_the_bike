include_directories(../include ${COMMON_TEST_INCLUDE_DIRS})
link_libraries(${PROJECT_LINK_LIBRARIES})

add_executable(mmath_test mmath.cpp)
add_executable(SDL_Draw_test SDL_Draw.cpp)
<<<<<<< HEAD
add_executable(test_test test.cpp)
=======
add_executable(test_test test.cpp)
add_executable(RectRectCollision_test RectRectCollision.cpp)
target_link_libraries(RectRectCollision_test ${COMMON_TEST_LIBRARIES})
>>>>>>> 5ba85be1135628b8bf11f3151f31eff1645a7b7e
