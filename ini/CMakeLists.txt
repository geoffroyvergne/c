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
    #BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

file(GLOB SOURCES_LIB true ${PROJECT_BINARY_DIR}/inih-prefix/src/inih/ini.c)
#set(SOURCES_LIB ${SOURCES_LIB})

#add_library(inihlib STATIC ${SOURCES_LIB})
#target_link_libraries(common ${CONAN_LIBS} ${LIB_COMMON})

include_directories(${PROJECT_BINARY_DIR}/inih-prefix/src/inih)
#add_executable(${PROJECT_NAME} ini-test.c ${PROJECT_BINARY_DIR}/inih-prefix/src/inih/ini.c)
add_executable(${PROJECT_NAME} ${SOURCES_LIB} ini-test.c)  
#target_link_libraries(${PROJECT_NAME} inihlib)

add_dependencies(${PROJECT_NAME} inih)

