#include "HashMap.h"
HashMap::HashMap(int cap = 100003) : capacity(cap), size(0)
{
    table.resize(cap, nullptr);
}
void insert(const std::string &ingredient, int recipeId)
{
}
std::vector<int> HashMap::search(const std::string &ingredient)
{
}