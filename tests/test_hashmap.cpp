#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "../src/structures/hashmap/HashMap.h"
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

TEST_CASE("HashMap: insert and search basic", "[hashmap]")
{
    HashMap hm(100);

    hm.insert("salt", 1);
    hm.insert("salt", 2);

    auto ids = hm.search("salt");

    REQUIRE(ids.size() == 2);
    CHECK((ids[0] == 1 || ids[1] == 1));
    CHECK((ids[0] == 2 || ids[1] == 2));
}

TEST_CASE("HashMap: search missing ingredient returns empty vector", "[hashmap]")
{
    HashMap hm(100);
    hm.insert("salt", 1);
    auto ids = hm.search("pepper");
    CHECK(ids.empty());
}

TEST_CASE("HashMap: handles collisions correctly", "[hashmap]")
{
    HashMap hm(5); // small capacity to force collisions

    hm.insert("salt", 1);
    hm.insert("salt", 2);
    hm.insert("salt", 3);

    auto ids = hm.search("salt");

    REQUIRE(ids.size() == 3);
    CHECK(std::find(ids.begin(), ids.end(), 1) != ids.end());
    CHECK(std::find(ids.begin(), ids.end(), 2) != ids.end());
    CHECK(std::find(ids.begin(), ids.end(), 3) != ids.end());
}

TEST_CASE("HashMap: constructor builds inverted index from recipes", "[hashmap]")
{
    auto recipes = makeRecipes();
    HashMap hm(recipes);

    auto saltIds = hm.search("salt");
    REQUIRE(saltIds.size() == 2);
    CHECK(std::find(saltIds.begin(), saltIds.end(), 1) != saltIds.end());
    CHECK(std::find(saltIds.begin(), saltIds.end(), 2) != saltIds.end());

    auto breadIds = hm.search("bread");
    REQUIRE(breadIds.size() == 1);
    CHECK(breadIds[0] == 3);
}

TEST_CASE("HashMap: query returns correct RecipeMatch results", "[hashmap]")
{
    auto recipes = makeRecipes();
    HashMap hm(recipes);

    std::vector<std::string> pantry = {"salt", "eggs"};

    auto results = hm.query(pantry);

    REQUIRE(results.size() == 2); // Pasta + Omelette

    auto omelette = std::find_if(results.begin(), results.end(),
                                 [](const RecipeMatch &rm)
                                 { return rm.recipe.id == 2; });
    REQUIRE(omelette != results.end());
    CHECK(omelette->score == Catch::Approx(2.0 / 3.0));
    CHECK(omelette->missing.size() == 1);
    CHECK(omelette->missing[0] == "pepper");

    auto pasta = std::find_if(results.begin(), results.end(),
                              [](const RecipeMatch &rm)
                              { return rm.recipe.id == 1; });
    REQUIRE(pasta != results.end());
    CHECK(pasta->score == Catch::Approx(1.0 / 3.0));
    CHECK(pasta->missing.size() == 2);
    CHECK((pasta->missing[0] == "pasta" || pasta->missing[1] == "pasta"));
    CHECK((pasta->missing[0] == "olive oil" || pasta->missing[1] == "olive oil"));
}

TEST_CASE("HashMap: empty pantry returns empty result", "[hashmap]")
{
    auto recipes = makeRecipes();
    HashMap hm(recipes);

    std::vector<std::string> pantry = {};
    auto results = hm.query(pantry);

    CHECK(results.empty());
}

TEST_CASE("HashMap: heap returns top N in correct order", "[hashmap][heap]")
{
    auto recipes = makeRecipes();
    HashMap hm(recipes);

    std::vector<std::string> pantry = {"salt", "eggs"};

    auto top2 = hm.getTopN(pantry, 2);

    REQUIRE(top2.size() == 2);

    CHECK(top2[0].recipe.title == "Omelette");
    CHECK(top2[0].score == Catch::Approx(2.0 / 3.0));

    CHECK(top2[1].recipe.title == "Pasta");
    CHECK(top2[1].score == Catch::Approx(1.0 / 3.0));
}

TEST_CASE("HashMap: heap handles N larger than result size", "[hashmap][heap]")
{
    auto recipes = makeRecipes();
    HashMap hm(recipes);

    std::vector<std::string> pantry = {"salt"};
    auto results = hm.query(pantry);

    auto top10 = hm.getTopN(pantry, 10);

    REQUIRE(top10.size() == 2);
}
