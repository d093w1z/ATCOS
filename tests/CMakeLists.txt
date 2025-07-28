include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP 1

)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


# Automatically find test source files
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Add test executable
add_executable(run_tests ${TEST_FILES})

# Link with gtest and your main library
target_link_libraries(run_tests PRIVATE ATCOS_lib GTest::gtest_main)

# Add test to CTest
include(GoogleTest)
gtest_discover_tests(run_tests)

# Automatically run tests after build
add_custom_command(
  TARGET run_tests
  POST_BUILD
  COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
)