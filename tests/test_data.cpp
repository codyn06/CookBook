#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <cstdio>
#include "data/data.h"

// parseStringifiedList

TEST_CASE("parseStringifiedList: multiple items", "[parser]")
{
    std::string input = R"(["1 c. sugar", "1/2 c. milk", "2 Tbsp. butter"])";
    auto result = parseStringifiedList(input);

    REQUIRE(result.size() == 3);
    CHECK(result[0] == "1 c. sugar");
    CHECK(result[1] == "1/2 c. milk");
    CHECK(result[2] == "2 Tbsp. butter");
}

TEST_CASE("parseStringifiedList: single item", "[parser]")
{
    auto result = parseStringifiedList(R"(["just one item"])");
    REQUIRE(result.size() == 1);
    CHECK(result[0] == "just one item");
}

TEST_CASE("parseStringifiedList: empty list", "[parser]")
{
    auto result = parseStringifiedList("[]");
    CHECK(result.empty());
}

TEST_CASE("parseStringifiedList: empty string input", "[parser]")
{
    auto result = parseStringifiedList("");
    CHECK(result.empty());
}

TEST_CASE("parseStringifiedList: item containing an apostrophe", "[parser]")
{
    auto result = parseStringifiedList(R"(["Grandma's spice mix", "1 tsp. salt"])");
    REQUIRE(result.size() == 2);
    CHECK(result[0] == "Grandma's spice mix");
    CHECK(result[1] == "1 tsp. salt");
}

TEST_CASE("parseStringifiedList: item containing parentheses and slashes", "[parser]")
{
    auto result = parseStringifiedList("[\"1/2 c. broken nuts (pecans)\"]");
    REQUIRE(result.size() == 1);
    CHECK(result[0] == "1/2 c. broken nuts (pecans)");
}

TEST_CASE("parseStringifiedList: real NER-style example from dataset", "[parser]")
{
    std::string input = R"(["brown sugar", "milk", "vanilla", "nuts", "butter", "bite size shredded rice biscuits"])";
    auto result = parseStringifiedList(input);
    REQUIRE(result.size() == 6);
    CHECK(result[0] == "brown sugar");
    CHECK(result[5] == "bite size shredded rice biscuits");
}

TEST_CASE("parseStringifiedList: backslash-escaped quote is not stripped (documents current bug)", "[parser][known-issue]")
{
    std::string input = R"(["she said \"hi\""])";
    auto result = parseStringifiedList(input);
    REQUIRE(result.size() == 1);
    CHECK(result[0] == R"(she said \"hi\")");
}

// loadRecipes

static std::string writeTestCsv()
{
    std::string path = "test_fixture.csv";
    std::ofstream out(path);
    out << ",title,ingredients,directions,link,source,NER\n";
    out << R"(0,No-Bake Nut Cookies,"[""1 c. firmly packed brown sugar"", ""1/2 c. evaporated milk""]","[""Mix ingredients."", ""Let stand until firm.""]",www.cookbooks.com/Recipe-Details.aspx?id=44874,Gathered,"[""brown sugar"", ""milk""]")" << "\n";
    out << R"(1,Simple Toast,"[""2 slices bread"", ""1 Tbsp. butter""]","[""Toast bread."", ""Spread butter.""]",www.example.com/toast,Gathered,"[""bread"", ""butter""]")" << "\n";
    out.close();
    return path;
}

// RAII File Guard: Automatically deletes the file when it goes out of scope
struct FileCleaner
{
    std::string filepath;
    FileCleaner(std::string path) : filepath(path) {}
    ~FileCleaner() { std::remove(filepath.c_str()); }
};

TEST_CASE("loadRecipes: parses row count and basic fields correctly", "[loader]")
{
    std::string path = writeTestCsv();
    FileCleaner cleaner(path);

    auto recipes = loadRecipes(path);

    REQUIRE(recipes.size() == 2);

    CHECK(recipes[0].id == 0);
    CHECK(recipes[0].title == "No-Bake Nut Cookies");
    CHECK(recipes[0].link == "www.cookbooks.com/Recipe-Details.aspx?id=44874");

    CHECK(recipes[1].id == 1);
    CHECK(recipes[1].title == "Simple Toast");
}

TEST_CASE("loadRecipes: ingredients, directions, and NER lists parse correctly", "[loader]")
{
    std::string path = writeTestCsv();
    FileCleaner cleaner(path);

    auto recipes = loadRecipes(path);
    REQUIRE(recipes.size() == 2);

    REQUIRE(recipes[0].ingredients.size() == 2);
    CHECK(recipes[0].ingredients[0] == "1 c. firmly packed brown sugar");
    CHECK(recipes[0].ingredients[1] == "1/2 c. evaporated milk");

    REQUIRE(recipes[0].directions.size() == 2);
    CHECK(recipes[0].directions[0] == "Mix ingredients.");

    REQUIRE(recipes[0].ner.size() == 2);
    CHECK(recipes[0].ner[0] == "brown sugar");
    CHECK(recipes[0].ner[1] == "milk");
}

TEST_CASE("loadRecipes: nonexistent file returns empty vector without crashing", "[loader]")
{
    auto recipes = loadRecipes("this_file_does_not_exist_12345.csv");
    CHECK(recipes.empty());
}

TEST_CASE("loadRecipes: handles a recipe with empty ingredient list", "[loader]")
{
    std::string path = "test_fixture_empty.csv";
    std::ofstream out(path);
    out << ",title,ingredients,directions,link,source,NER\n";
    out << R"(0,Mystery Dish,"[]","[]",www.example.com,Gathered,"[]")" << "\n";
    out.close();

    FileCleaner cleaner(path);

    auto recipes = loadRecipes(path);
    REQUIRE(recipes.size() == 1);
    CHECK(recipes[0].ingredients.empty());
    CHECK(recipes[0].directions.empty());
    CHECK(recipes[0].ner.empty());
}