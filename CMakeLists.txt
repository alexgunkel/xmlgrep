cmake_policy( SET CMP0048 NEW )
project(xmlgrep VERSION 1)

cmake_minimum_required(VERSION 3.20)

include(cmake/gtest-config.cmake)
include(cmake/cli11-config.cmake)

add_subdirectory(src)
