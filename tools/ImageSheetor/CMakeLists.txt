set(EXE_NAME ImageSheetor)
set(ImageSheetor_VERSION_MAJOR 1)
set(ImageSheetor_VERSION_MAJOR 1)

include_directories(include ${JsonCpp_INCLUDE_DIRS})
link_libraries(${JsonCpp_LIBRARIES} ${SDL_TOTLE_LIBRARIES})

aux_source_directory(src ImageSheet_SRC)

set(ImageSheetReader_LIBNAME ImageSheetReader)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(${ImageSheetReader_LIBNAME} src/imagesheetreader.cpp src/imagesheet.cpp)

set(COMMON_Rely_SRC ${COMMON_SRC_DIRS}/engin/collisionapproch.cpp)

add_executable(${EXE_NAME} main.cpp ${ImageSheet_SRC} ${COMMON_Rely_SRC})

add_subdirectory(test)
