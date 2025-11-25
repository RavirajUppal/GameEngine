cmake_minimum_required(VERSION 3.21)

project(Engine LANGUAGES C CXX)

file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

# add_library(Engine SHARED ${ENGINE_SOURCES})

set(GLAD_SRC Vendor/glad/src/glad.c)

add_library(Engine SHARED
    ${ENGINE_SOURCES}
    ${GLAD_SRC}
)

target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glad/include
)

target_precompile_headers(Engine PUBLIC
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h>"
)

target_compile_definitions(Engine
    PUBLIC
        REALENGINE_BUILD_DLL
        REALENGINE_ENABLE_ASSERTS
)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Engine PUBLIC DEBUG)
else()
    target_compile_definitions(Engine PUBLIC NDEBUG)
endif()


if(APPLE)
    message(STATUS "Configuring Engine for macOS")

    # Find GLFW manually since pkg-config isn't available
    set(GLFW_ROOT "/opt/homebrew/opt/glfw")
    
    find_path(GLFW_INCLUDE_DIR NAMES GLFW/glfw3.h PATHS "${GLFW_ROOT}/include")
    find_library(GLFW_LIBRARY NAMES glfw PATHS "${GLFW_ROOT}/lib")
    
    if(NOT GLFW_INCLUDE_DIR OR NOT GLFW_LIBRARY)
        message(FATAL_ERROR "Could not find GLFW. Make sure it's installed with Homebrew.")
    endif()
    
    
    # Include directories
    target_include_directories(Engine PUBLIC
        ${GLFW_INCLUDE_DIR}
        /opt/homebrew/include # GLFW and GLM
    )
    
    # Link libraries
    target_link_libraries(Engine
        ${GLFW_LIBRARY}
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )


elseif(WIN32)
    message(STATUS "Configuring Engine for Windows")

    include(FetchContent)

    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
    )
    FetchContent_MakeAvailable(glfw)

    target_link_libraries(Engine PUBLIC
        glfw
        opengl32
    )

endif()
