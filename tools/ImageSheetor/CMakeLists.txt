set(EXE_NAME ImageSheetor)

include_directories(include ${JsonCpp_INCLUDE_DIRS})
link_libraries(${JsonCpp_LIBRARIES} ${PROJECT_LINK_LIBRARIES})

aux_source_directory(src ImageSheet_SRC)

set(ImageSheetReader_LIBNAME ImageSheetReader)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(${ImageSheetReader_LIBNAME} src/imagesheetreader.cpp src/imagesheet.cpp)

add_executable(${EXE_NAME} main.cpp ${ImageSheet_SRC})

add_subdirectory(test)

