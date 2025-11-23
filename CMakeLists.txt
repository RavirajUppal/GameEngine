cmake_minimum_required(VERSION 3.21)

# ----------- Project ----------
project(MyGameEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable folders in Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ----------- Subdirectories -----------
add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Game)
