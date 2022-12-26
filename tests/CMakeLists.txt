cmake_minimum_required(VERSION 3.21)

project(tests)
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        hello_test
        hello_test.cpp
        helpers.h
        helpers.cpp
        GraphWindowTests.cpp
        GraphControllerTests.cpp
)
target_include_directories(hello_test PRIVATE ${GTKMM_INCLUDE_DIRS})
target_compile_options(hello_test PRIVATE ${GTKMM_CFLAGS_OTHER})
#target_link_libraries(hello_test ${GTKMM_LIBRARIES} Threads::Threads)

target_link_libraries(hello_test procmon_lib)
target_link_directories(hello_test PRIVATE ../cmake-build-debug/src)
target_link_libraries(hello_test GTest::gtest_main)
target_link_libraries(procmon procmon_lib ${GTKMM_LIBRARIES} Threads::Threads)

target_include_directories(hello_test PRIVATE ../src)
include(GoogleTest)
gtest_discover_tests(hello_test)
