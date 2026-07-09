#include "Graph.h"
#include <unordered_set>
#include <queue>

Graph::Graph(const std::vector<Recipe> &recipes)
{
    for (const auto &r : recipes)
    {
        recipeLookup[r.id] = r;

        for (const auto &ing : r.ner)
        {
            adjacencyList[ing].push_back(r.id);
        }
    }
}

std::vector<RecipeMatch> Graph::query(const std::vector<std::string> &pantry)
{
    std::unordered_map<int, int> matchCounts;

    for (const auto &ing : pantry)
    {
        auto it = adjacencyList.find(ing);
        if (it != adjacencyList.end())
        {
            for (int recipeId : it->second)
            {
                matchCounts[recipeId]++;
            }
        }
    }

    std::unordered_set<std::string> pantrySet(pantry.begin(), pantry.end());
    std::vector<RecipeMatch> results;

    for (const auto &pair : matchCounts)
    {
        int recipeId = pair.first;
        int matches = pair.second;

        const Recipe &r = recipeLookup.at(recipeId);

        int total = r.ner.size();
        double score = static_cast<double>(matches) / total;

        std::vector<std::string> missing;
        for (const auto &ing : r.ner)
        {
            if (!pantrySet.count(ing))
            {
                missing.push_back(ing);
            }
        }

        results.push_back({r, score, missing});
    }

    return results;
}

