include_directories(../include)
link_libraries(${PROJECT_LINK_LIBRARIES})

aux_source_directory(../src I_WANNA_SRC)

add_executable(particalSystemGUI_test particalSystemGUI.cpp ${I_WANNA_SRC})
