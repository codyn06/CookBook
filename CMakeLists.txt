cmake_minimum_required(VERSION 4.1)
project(Project_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project_2 src/main.cpp
        src/data/data.h
        src/data/data.cpp
        src/data/Recipe.h
        src/structures/hashmap/HashMap.cpp
        src/structures/hashmap/HashMap.h
        src/structures/graph/Graph.cpp
        src/structures/graph/Graph.h)
