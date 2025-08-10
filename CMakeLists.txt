cmake_minimum_required(VERSION 3.12.0)
project(ATCOS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-p=${CMAKE_BINARY_DIR}")


# Set Tracy defines
set(TRACY_ENABLE)
# set(TRACY_VERBOSE ON)
set(TRACY_ON_DEMAND ON)

add_subdirectory(src)

enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)

add_subdirectory(${CMAKE_SOURCE_DIR}/third-party)

option(ENABLE_CLANG_TIDY "Enable clang-tidy linting" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(${CMAKE_SOURCE_DIR}/GameConfiguration.toml ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GameConfiguration.toml COPYONLY)

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE} -checks=clang-analyzer-*,modernize-*,performance-*")
    endif()
endif()