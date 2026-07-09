#ifndef GRAPH_H
#define GRAPH_H

#include "../Structure.h"
#include "../../data/Recipe.h"
#include <unordered_map>
#include <string>
#include <vector>

class Graph : public Structure
{
private:
    std::unordered_map<std::string, std::vector<int>> adjacencyList;
    std::unordered_map<int, Recipe> recipeLookup;

public:
    Graph(const std::vector<Recipe> &recipes);
    std::vector<RecipeMatch> query(const std::vector<std::string> &pantry) override;
};

#endif // GRAPH_H
