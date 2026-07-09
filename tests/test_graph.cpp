#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "../src/structures/graph/Graph.h"
#include "../src/data/Recipe.h"

static std::vector<Recipe> makeRecipes()
{
    Recipe r1;
    r1.id = 1;
    r1.title = "Pasta";
    r1.ner = {"pasta", "salt", "olive oil"};

    Recipe r2;
    r2.id = 2;
    r2.title = "Omelette";
    r2.ner = {"eggs", "salt", "pepper"};

    Recipe r3;
    r3.id = 3;
    r3.title = "Toast";
    r3.ner = {"bread", "butter"};

    return {r1, r2, r3};
}

TEST_CASE("Graph: adjacency list builds correctly", "[graph]")
{
    auto recipes = makeRecipes();
    Graph g(recipes);

    auto saltList = g.getAdjacencyList().at("salt");
    REQUIRE(saltList.size() == 2);
    CHECK((saltList[0] == 1 || saltList[1] == 1));
    CHECK((saltList[0] == 2 || saltList[1] == 2));

    auto breadList = g.getAdjacencyList().at("bread");
    REQUIRE(breadList.size() == 1);
    CHECK(breadList[0] == 3);
}

TEST_CASE("Graph: query computes correct scores", "[graph]")
{
    auto recipes = makeRecipes();
    Graph g(recipes);

    std::vector<std::string> pantry = {"salt", "eggs"};
    auto results = g.query(pantry);

    REQUIRE(results.size() == 2);

    auto omelette = std::find_if(results.begin(), results.end(),
                                 [](const RecipeMatch &rm)
                                 { return rm.recipe.id == 2; });
    REQUIRE(omelette != results.end());
    CHECK(omelette->score == Catch::Approx(2.0 / 3.0));

    auto pasta = std::find_if(results.begin(), results.end(),
                              [](const RecipeMatch &rm)
                              { return rm.recipe.id == 1; });
    REQUIRE(pasta != results.end());
    CHECK(pasta->score == Catch::Approx(1.0 / 3.0));
}

TEST_CASE("Graph: missing ingredients computed correctly", "[graph]")
{
    auto recipes = makeRecipes();
    Graph g(recipes);

    std::vector<std::string> pantry = {"salt", "eggs"};
    auto results = g.query(pantry);

    auto omelette = std::find_if(results.begin(), results.end(),
                                 [](const RecipeMatch &rm)
                                 { return rm.recipe.id == 2; });
    REQUIRE(omelette != results.end());
    REQUIRE(omelette->missing.size() == 1);
    CHECK(omelette->missing[0] == "pepper");

    auto pasta = std::find_if(results.begin(), results.end(),
                              [](const RecipeMatch &rm)
                              { return rm.recipe.id == 1; });
    REQUIRE(pasta != results.end());
    REQUIRE(pasta->missing.size() == 2);
    CHECK((pasta->missing[0] == "pasta" || pasta->missing[1] == "pasta"));
    CHECK((pasta->missing[0] == "olive oil" || pasta->missing[1] == "olive oil"));
}

TEST_CASE("Graph: heap returns top N in correct order", "[graph][heap]")
{
    auto recipes = makeRecipes();
    Graph g(recipes);

    std::vector<std::string> pantry = {"salt", "eggs"};

    auto top2 = g.getTopN(pantry, 2);

    REQUIRE(top2.size() == 2);

    CHECK(top2[0].recipe.title == "Omelette");
    CHECK(top2[0].score == Catch::Approx(2.0 / 3.0));

    CHECK(top2[1].recipe.title == "Pasta");
    CHECK(top2[1].score == Catch::Approx(1.0 / 3.0));
}

TEST_CASE("Graph: heap handles N larger than result size", "[graph][heap]")
{
    auto recipes = makeRecipes();
    Graph g(recipes);

    std::vector<std::string> pantry = {"salt"};
    auto results = g.query(pantry);

    auto top10 = g.getTopN(pantry, 10);

    REQUIRE(top10.size() == 2);
}

TEST_CASE("Graph: empty pantry returns empty result", "[graph]")
{
    auto recipes = makeRecipes();
    Graph g(recipes);

    std::vector<std::string> pantry = {};
    auto results = g.query(pantry);

    CHECK(results.empty());
}
