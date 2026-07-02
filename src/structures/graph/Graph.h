#ifndef GRAPH_H
#define GRAPH_H

#include "../Structure.h"
class Graph : public Structure
{
    Graph(std::vector<Recipe> &recipes);
    std::vector<Recipe> query(const std::vector<std::string> &pantry) override;
};

#endif // GRAPH_H