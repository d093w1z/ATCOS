# Collect all source files
file(GLOB_RECURSE LIB_SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE UTIL_SRC_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/utils/*.cpp)

# Create a shared or static library
add_library(ATCOS_lib ${LIB_SRC_FILES} ${UTIL_SRC_FILES})
target_include_directories(ATCOS_lib PUBLIC ${CMAKE_SOURCE_DIR}/src/lib ${CMAKE_SOURCE_DIR}/src/utils)
target_link_libraries(ATCOS_lib PUBLIC spdlog tomlplusplus::tomlplusplus PUBLIC TracyClient)

# Platform-specific flags (optional)
if (WIN32)
    target_compile_definitions(ATCOS_lib PRIVATE PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(ATCOS_lib PRIVATE PLATFORM_MAC)
elseif(UNIX)
    target_compile_definitions(ATCOS_lib PRIVATE PLATFORM_LINUX)
endif()
set_target_properties(ATCOS_lib PROPERTIES FOLDER "Libraries")
