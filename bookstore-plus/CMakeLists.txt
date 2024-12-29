cmake_minimum_required(VERSION 3.29)
project(bookstore_plus)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        bookstore_plus main.cpp
        storage.h
        storage.cpp
        booksystem.cpp
        booksystem.h
        tools.cpp
        tools.h
        usersystem.cpp
        usersystem.h
        logsystem.cpp
        logsystem.h
        logsystem.cpp
)
