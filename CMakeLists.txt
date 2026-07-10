cmake_minimum_required(VERSION 3.14)
project(CookBook)

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

add_executable(CookBook
        src/main.cpp

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
        src/gui/flowlayout.h
        src/gui/flowlayout.cpp
        src/gui/RecipeCard.h
        src/gui/RecipeCard.cpp
        src/gui/ResultsScreen.h
        src/gui/ResultsScreen.cpp
        src/gui/StructureSelect.h
        src/gui/StructureSelect.cpp
        src/gui/mainwindow.h
        src/gui/mainwindow.cpp
)

target_include_directories(CookBook PRIVATE src)
target_link_libraries(CookBook PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

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

add_executable(Test_IngredientInput
        tests/test_ingredientinput.cpp
        src/gui/ingredientinput.cpp
        src/gui/flowlayout.cpp
)

target_include_directories(Test_IngredientInput PRIVATE src)
target_link_libraries(Test_IngredientInput PRIVATE Qt6::Widgets)

add_executable(Test_Results
        tests/test_results.cpp
        
        src/gui/ResultsScreen.h
        src/gui/ResultsScreen.cpp
        src/gui/RecipeCard.h
        src/gui/RecipeCard.cpp

        src/data/data.h
        src/data/data.cpp
        src/data/Recipe.h
        src/structures/Structure.h
)

target_include_directories(Test_Results PRIVATE src)
target_link_libraries(Test_Results PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

add_executable(Test_StructureSelect
        tests/test_structureselect.cpp
        
        src/gui/StructureSelect.h
        src/gui/StructureSelect.cpp
)

target_include_directories(Test_StructureSelect PRIVATE src)
target_link_libraries(Test_StructureSelect PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

add_executable(Test_MainWindow
        tests/test_mainwindow.cpp
        
        src/gui/mainwindow.h
        src/gui/mainwindow.cpp
        
        src/gui/IngredientInput.h
        src/gui/IngredientInput.cpp
        src/gui/flowlayout.h
        src/gui/flowlayout.cpp
        src/gui/StructureSelect.h
        src/gui/StructureSelect.cpp
        src/gui/ResultsScreen.h
        src/gui/ResultsScreen.cpp
        src/gui/RecipeCard.h
        src/gui/RecipeCard.cpp

        src/data/data.h
        src/data/data.cpp
        src/data/Recipe.h
        src/structures/Structure.h
        src/structures/hashmap/HashMap.h
        src/structures/hashmap/HashMap.cpp
        src/structures/graph/Graph.h
        src/structures/graph/Graph.cpp
)

target_include_directories(Test_MainWindow PRIVATE src)
target_link_libraries(Test_MainWindow PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

include(CTest)
include(Catch)
catch_discover_tests(Tests)