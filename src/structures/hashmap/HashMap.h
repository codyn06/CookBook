#ifndef HASHMAP_H
#define HASHMAP_H

#include "../Structure.h"

struct HashNode
{
    std::string ingredient;
    std::vector<int> recipeIds;
    HashNode *next;

    HashNode(std::string i) : ingredient(i), next(nullptr) {}
};

class HashMap : public Structure
{
private:
    int hashFunction(const std::string &ingredient);

public:
    HashMap(std::vector<Recipe> &recipes);
    void insert(const std::string &ingredient, int recipeId);
    std::vector<int> search(const std::string &ingredient);
    std::vector<Recipe> query(const std::vector<std::string> &pantry) override;
};

#endif // HASHMAP_H