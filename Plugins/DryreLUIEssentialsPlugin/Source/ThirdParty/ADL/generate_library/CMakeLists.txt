# Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
cmake_minimum_required (VERSION 3.8)

set(library_name "ADLManager")

project(${library_name})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/../../ADL/dll/Release/)
include_directories(
D:/GithubRepos/DryreLUIEssentials/Plugins/DryreLUIEssentialsPlugin/Source/ThirdParty/ADL/include
)

set(all_file
  ${CMAKE_CURRENT_SOURCE_DIR}/ADLManager.h
  ${CMAKE_CURRENT_SOURCE_DIR}/ADLManager.cpp
  D:/GithubRepos/DryreLUIEssentials/Plugins/DryreLUIEssentialsPlugin/Source/ThirdParty/ADL/ADLXHelper/Windows/Cpp/ADLXHelper.h
  D:/GithubRepos/DryreLUIEssentials/Plugins/DryreLUIEssentialsPlugin/Source/ThirdParty/ADL/ADLXHelper/Windows/Cpp/ADLXHelper.cpp
  D:/GithubRepos/DryreLUIEssentials/Plugins/DryreLUIEssentialsPlugin/Source/ThirdParty/ADL/Platform/Windows/WinAPIs.cpp
)

# Create a shared library
add_library(${library_name} SHARED ${all_file})
