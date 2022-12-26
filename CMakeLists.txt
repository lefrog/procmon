cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)

project(procmon C CXX)

#set(PROJECT_TARGET procmon)

find_package(PkgConfig REQUIRED)
find_package(Threads)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

add_subdirectory(src)
add_subdirectory(tests)

