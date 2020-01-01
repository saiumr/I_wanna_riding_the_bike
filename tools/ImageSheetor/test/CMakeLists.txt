aux_source_directory(../src TOOL_SRC)

add_executable(ImageSheetWriter_test ImageSheetWriter.cpp ${TOOL_SRC})
add_executable(ImageSheetReader_test ImageSheetReader.cpp ${TOOL_SRC})