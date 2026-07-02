#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>
#include "../data/Recipe.h"

class Structure
{
public:
    virtual ~Structure() = default;
    virtual std::vector<Recipe> query(const std::vector<std::string> &pantry) = 0;
};

#endif // STRUCTURE_H