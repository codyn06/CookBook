#include "Graph.h"

#include <unordered_set>

Graph::Graph(const std::vector<Recipe> &recipes) {
    for (const auto &recipe : recipes) {
        recipeLookup[recipe.id] = recipe;

        for (const auto &ingredient: recipe.ner) {
            adjacencyList[ingredient].push_back(recipe.id);
        }
    }
}

std::vector<RecipeMatch> Graph::query(const std::vector<std::string> &pantry) {
    std::unordered_map<int, int> matchCounts;

    for (const auto &pantryIng : pantry) {
        auto it = adjacencyList.find(pantryIng);
        if (it != adjacencyList.end()) {
            for (int recipeId : it->second) {
                matchCounts[recipeId]++;
            }
        }
    }

    std::vector<RecipeMatch> results;

    for (const auto &pair : matchCounts) {
        int recipeId = pair.first;
        int matches = pair.second;

        const Recipe &r = recipeLookup[recipeId];

        int totalIngredients = r.ner.size();
        double score = static_cast<double>(matches) / totalIngredients;

        std::unordered_set<std::string> pantrySet(pantry.begin(), pantry.end());
        std::vector<std::string> missing;

        for (const auto &ing : r.ner) {
            if (pantrySet.find(ing) == pantrySet.end()) {
                missing.push_back(ing);
            }
        }

        results.push_back({r, score, missing});
    }

    return results;
}
