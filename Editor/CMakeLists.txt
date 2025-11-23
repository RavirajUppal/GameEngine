cmake_minimum_required(VERSION 3.21)

project(Editor LANGUAGES C CXX)

file(GLOB_RECURSE EDITOR_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(Editor ${EDITOR_SOURCES})

target_link_libraries(Editor PRIVATE Engine)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Editor PUBLIC DEBUG)
else()
    target_compile_definitions(Editor PUBLIC NDEBUG)
endif()
