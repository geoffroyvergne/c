set(BINARY ${CMAKE_PROJECT_NAME}_test)
set(LIB_COMMON common)

# Add conan dependencies
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${BINARY} ${SOURCES_TEST})
#add_library(${LIB} STATIC ${SOURCES})

target_link_libraries(${BINARY} ${CONAN_LIBS} ${LIB_COMMON})

# Copy binary to build/test
add_custom_command(TARGET ${BINARY} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${BINARY}> ../bin/${BINARY})
