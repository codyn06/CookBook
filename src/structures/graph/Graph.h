#ifndef GRAPH_H
#define GRAPH_H

#include "../Structure.h"
#include <map>
class Graph : public Structure
{
private:
    std::map<std::string, std::vector<int>> adjacencyList;
    std::vector<int> recipeDegrees;

public:
    Graph(const std::vector<Recipe> &recipes);
    std::vector<Recipe> query(const std::vector<std::string> &pantry) override;
};

#endif // GRAPH_H