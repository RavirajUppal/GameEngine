project(Game LANGUAGES C CXX)

file(GLOB_RECURSE GAME_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(Game ${GAME_SOURCES})

target_link_libraries(Game PRIVATE Engine)

# Copy the Engine.dylib next to Game
add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:Engine> $<TARGET_FILE_DIR:Game>
)

# set_target_properties(Game PROPERTIES
#     BUILD_RPATH "@executable_path"
# )

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Game PUBLIC DEBUG)
else()
    target_compile_definitions(Game PUBLIC NDEBUG)
endif()