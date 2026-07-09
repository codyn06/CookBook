#include "structures/graph/Graph.h"
#include "catch2/catch_test_macros.hpp"
#include "data/data.h"
#include "structures/hashmap/HashMap.h"

TEST_CASE("Integration: loader + hashmap + graph + query + ranking", "[integration]") {

    auto recipes = loadRecipes("../dataset/full_dataset.csv");
    REQUIRE(!recipes.empty());

    HashMap hm(recipes);
    Graph g(recipes);

    std::vector<std::string> pantry = {"salt", "eggs", "butter"};

    auto hm_results = hm.query(pantry);

    REQUIRE(!hm_results.empty());

    auto top5 = g.getTopN(pantry, 5);

    REQUIRE(!top5.empty());
    REQUIRE(top5.size() <= 5);

    for (const auto& match : top5) {
        CHECK(match.score >= 0.0);
        CHECK(match.score <= 1.0);
    }

    for (const auto& match : top5) {
        for (const auto& ing : match.missing) {
            CHECK(std::find(pantry.begin(), pantry.end(), ing) == pantry.end());
        }
    }
}

TEST_CASE("Integration: empty pantry produces empty results", "[integration]") {
    auto recipes = loadRecipes("dataset/full_dataset.csv");
    REQUIRE(!recipes.empty());

    HashMap hm(recipes);
    Graph g(recipes);

    std::vector<std::string> pantry = {};

    auto hm_results = hm.query(pantry);
    auto g_results = g.query(pantry);

    CHECK(hm_results.empty());
    CHECK(g_results.empty());
}
