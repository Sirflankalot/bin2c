cmake_minimum_required(VERSION 3.0.1)
project(bin2c VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Release)

add_executable(bin2c bin2c.cpp)

include(bin2c.cmake)

# bin2c(LENGTH 20
# 	  OUTPUT gitignore.cpp 
# 	  HEADER what.hpp
# 	  ARRAYS "gitignore .gitignore" )

# add_library(blah STATIC gitignore.cpp)