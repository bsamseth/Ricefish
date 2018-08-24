cmake_minimum_required(VERSION 3.10)
project(chinese_checkers)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(chinese_checkers
        src/board.cpp
        src/board.hpp
        src/interface.cpp
        src/interface.hpp
        src/main.cpp
        src/search.cpp
        src/search.hpp
        src/types.hpp
        )
