cmake_minimum_required(VERSION 3.10)
project(http-server VERSION 1.0)

set(C_STANDARD 11)

include(ExternalProject)

ExternalProject_Add(
    inih
    GIT_REPOSITORY https://github.com/jacklicn/CUnit.git
    GIT_TAG v2.1-3
    #UPDATE_COMMAND ""
    #INSTALL_COMMAND ""
    #BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND "autoreconf -vif"
    BUILD_COMMAND ${MAKE}
    INSTALL_COMMAND "make install"
)

