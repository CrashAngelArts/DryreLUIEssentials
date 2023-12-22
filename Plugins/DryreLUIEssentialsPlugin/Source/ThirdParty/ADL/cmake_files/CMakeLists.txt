cmake_minimum_required(VERSION 3.8)

set(project "PerfAllMetrics")

project(${project} CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../build/lib/)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../)

set(all_file
    "mainPerfAllMetrics.cpp"
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../SDK/ADLXHelper/Windows/Cpp/ADLXHelper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../SDK/platform/Windows/WinAPIs.cpp
)

add_library(${project} STATIC ${all_file})

set_target_properties(${project} PROPERTIES OUTPUT_NAME PerfAllMetrics)

target_link_libraries(${project} OtherLibrary1 OtherLibrary2)

install(TARGETS ${project} DESTINATION /path/to/installation/directory)
