cmake_minimum_required(VERSION 3.14)
project(artilleryi)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)


add_executable(
    artilleryi
    src/artilleryi.cxx
)


