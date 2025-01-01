cmake_minimum_required(VERSION 3.29)
project(code)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        code code.cpp
        storage.cpp
        tools.cpp
        booksystem.cpp
        logsystem.cpp
        usersystem.cpp
        booksystem.cpp
        logsystem.cpp
)
