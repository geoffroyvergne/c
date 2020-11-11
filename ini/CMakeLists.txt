cmake_minimum_required(VERSION 2.8.12)
project(initest)

set(C_STANDARD 11)

include(ExternalProject)

ExternalProject_Add(
    inih
    GIT_REPOSITORY https://github.com/benhoyt/inih.git
    GIT_TAG r52
    #UPDATE_COMMAND ""
    #INSTALL_COMMAND ""
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

file(GLOB SOURCES true *.c ${CMAKE_BINARY_DIR}/inih-prefix/src/inih/ini.c)
set(SOURCES ${SOURCES})

include_directories(${CMAKE_BINARY_DIR}/inih-prefix/src/inih)
add_executable(${PROJECT_NAME} ${SOURCES})  
