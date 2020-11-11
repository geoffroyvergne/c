cmake_minimum_required(VERSION 2.8.12)
project(initest)

set(C_STANDARD 11)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.c)
set(SOURCES ${SOURCES})

#add_library(inihlib STATIC ${SOURCES_LIB})
#target_link_libraries(common ${CONAN_LIBS} ${LIB_COMMON})

include_directories(include)
#add_executable(${PROJECT_NAME} ini-test.c ${PROJECT_BINARY_DIR}/inih-prefix/src/inih/ini.c)
add_executable(${PROJECT_NAME} ${SOURCES})  
#target_link_libraries(${PROJECT_NAME} inihlib)
