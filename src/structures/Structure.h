#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>
#include <string>
#include "../data/Recipe.h"

struct RecipeMatch
{
    Recipe recipe;
    double score;
    std::vector<std::string> missing;
};

class Structure
{
public:
    virtual ~Structure() = default;
    virtual std::vector<RecipeMatch> query(const std::vector<std::string> &pantry) = 0;
};

#endif // STRUCTURE_H
