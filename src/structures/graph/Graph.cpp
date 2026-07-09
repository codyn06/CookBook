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

std::vector<RecipeMatch> Graph::getTopN(const std::vector<std::string> &pantry, int N)
{
    std::vector<RecipeMatch> matches = query(pantry);

    auto cmp = [](const RecipeMatch &a, const RecipeMatch &b) {
        return a.score < b.score;
    };

    std::priority_queue<
        RecipeMatch,
        std::vector<RecipeMatch>,
        decltype(cmp)>
        pq(cmp);

    for (const auto &m : matches)
    {
        pq.push(m);
    }

    std::vector<RecipeMatch> topN;
    for (int i = 0; i < N && !pq.empty(); i++) {
        topN.push_back(pq.top());
        pq.pop();
    }

    return topN;
}
