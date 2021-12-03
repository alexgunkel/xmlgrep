cmake_policy( SET CMP0048 NEW )
project(xmlgrep VERSION 1)

cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(XMLGREP_SAMPLE_DIR ${CMAKE_SOURCE_DIR}/samples)

include(cmake/gtest-config.cmake)
include(cmake/cli11-config.cmake)

add_subdirectory(src)
