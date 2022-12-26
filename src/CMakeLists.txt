cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)

#project(procmon_lib)

set(SOURCES
        GraphWindow.cpp GraphWindow.h
        LoadWidget.cpp LoadWidget.h
        CLIMonitoring.cpp
        DataPoints.cpp DataPoints.h
        GraphController.cpp GraphController.h
        )

add_library(procmon_lib STATIC ${SOURCES})
target_include_directories(procmon_lib PRIVATE ${GTKMM_INCLUDE_DIRS})
target_compile_options(procmon_lib PRIVATE ${GTKMM_CFLAGS_OTHER})
target_link_libraries(procmon_lib ${GTKMM_LIBRARIES} Threads::Threads)

add_executable(
        procmon
        main.cpp
        ${SOURCE}
)
target_include_directories(procmon PRIVATE ${GTKMM_INCLUDE_DIRS})
#target_link_directories(procmon PRIVATE ${GTKMM_LIBRARY_DIRS} Threads::Threads)
target_compile_options(procmon PRIVATE ${GTKMM_CFLAGS_OTHER})
target_link_libraries(procmon procmon_lib ${GTKMM_LIBRARIES} Threads::Threads)
