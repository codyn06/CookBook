#include "Graph.h"

Graph::Graph(const std::vector<Recipe> &recipes)
{
    recipeDegrees.resize(recipes.size(), 0);

    for (const auto &r : recipes)
    {
        recipeDegrees[r.id] = r.ner.size();

        for (const auto &ingredient : r.ner)
        {
            adjacencyList[ingredient].push_back(r.id);
        }
    }
}