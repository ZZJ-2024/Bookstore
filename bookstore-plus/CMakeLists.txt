cmake_minimum_required(VERSION 3.29)
project(bookstore_plus)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        bookstore_plus main.cpp
        storage.cpp
        tools.cpp
        booksystem.cpp
        logsystem.cpp
        usersystem.cpp
)
