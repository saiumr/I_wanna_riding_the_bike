include_directories(../include)

aux_source_directory(../src TEST_SRC)
aux_source_directory(../src/controllers TEST_SRC)
aux_source_directory(../src/scenes TEST_SRC)

add_executable(particalSystemGUI_test particalSystemGUI.cpp ${TEST_SRC})
