cmake_minimum_required(VERSION 3.14)
project(Project_2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core Widgets Gui REQUIRED)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(Project_2
        src/main.cpp

        # Backend
        src/data/data.h
        src/data/data.cpp
        src/data/Recipe.h
        src/structures/Structure.h
        src/structures/hashmap/HashMap.cpp
        src/structures/hashmap/HashMap.h
        src/structures/graph/Graph.cpp
        src/structures/graph/Graph.h
        src/gui/IngredientInput.h
        src/gui/IngredientInput.cpp
)

target_include_directories(Project_2 PRIVATE src)
target_link_libraries(Project_2 PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

add_executable(Tests
        tests/test_data.cpp
        src/data/data.cpp
        src/data/data.h
        src/data/Recipe.h
        tests/test_graph.cpp
        src/structures/graph/Graph.cpp
        src/structures/hashmap/HashMap.cpp
        tests/test_hashmap.cpp
)

target_include_directories(Tests PRIVATE src)
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)

add_executable(Test_Integration
        tests/test_integration.cpp
        src/data/data.cpp
        src/data/data.h
        src/data/Recipe.h
        src/structures/graph/Graph.cpp
        src/structures/hashmap/HashMap.cpp
)

target_include_directories(Test_Integration PRIVATE src)
target_link_libraries(Test_Integration PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(Tests)