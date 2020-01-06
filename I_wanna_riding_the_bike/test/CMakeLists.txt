include_directories(../include)
link_libraries(${PROJECT_LINK_LIBRARIES})

<<<<<<< HEAD
aux_source_directory(../src TEST_SRC)
aux_source_directory(../src/controllers TEST_SRC)
aux_source_directory(../src/scenes TEST_SRC)

add_executable(particalSystemGUI_test particalSystemGUI.cpp ${TEST_SRC})
=======
aux_source_directory(../src I_WANNA_SRC)

add_executable(particalSystemGUI_test particalSystemGUI.cpp ${I_WANNA_SRC})
>>>>>>> 5ba85be1135628b8bf11f3151f31eff1645a7b7e
