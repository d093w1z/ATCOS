

# Main executable
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(ATCOS ${SRC_FILES} )
target_link_libraries(ATCOS PRIVATE ATCOS_lib PRIVATE SFML::Graphics PRIVATE spdlog tomlplusplus::tomlplusplus)
target_include_directories(ATCOS PUBLIC ${CMAKE_SOURCE_DIR}/src)

# Set folders for IDEs (like VS or CLion)
set_target_properties(ATCOS PROPERTIES FOLDER "Executables")
