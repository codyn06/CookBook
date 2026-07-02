#ifndef HASHMAP_H
#define HASHMAP_H

#include "../Structure.h"
class HashMap : public Structure
{
public:
    HashMap(std::vector<Recipe> &recipes);
    std::vector<Recipe> query(const std::vector<std::string> &pantry) override;
};

#endif // HASHMAP_H