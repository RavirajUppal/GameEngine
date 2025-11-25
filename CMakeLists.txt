cmake_minimum_required(VERSION 3.21...4.0)

if(APPLE)
    set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE STRING "" FORCE)
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "" FORCE)
endif()

# ----------- Project ----------
project(RealEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable folders in Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ----------- Subdirectories -----------
add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Game)
