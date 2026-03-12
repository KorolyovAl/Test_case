cmake_minimum_required(VERSION 3.22)

project(myList)

add_executable(myList 
    main.cpp
    my_list.h
)

add_executable(tests
    tests.cpp
    my_list.h
)