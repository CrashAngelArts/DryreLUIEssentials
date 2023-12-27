# Copyright (c) NVIDIA. All rights reserved.

cmake_minimum_required (VERSION 3.8)

set(library_name "NVMLManager")

project(${library_name})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/../../NVML/dll/)
include_directories(
D:/GithubRepos/DryreLUIEssentials/Plugins/DryreLUIEssentialsPlugin/Source/ThirdParty/NVML/include
)

set(all_file
  ${CMAKE_CURRENT_SOURCE_DIR}/NVMLManager.h
  ${CMAKE_CURRENT_SOURCE_DIR}/NVMLManager.cpp
)

# Create a shared library
add_library(${library_name} SHARED ${all_file})
