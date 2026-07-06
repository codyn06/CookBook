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
    std::vector<HashNode *> table;
    int capacity;
    int size;

    int hashFunction(const std::string &ingredient);

public:
    HashMap(const std::vector<Recipe> &recipes);
    HashMap(int cap);
    void insert(const std::string &ingredient, int recipeId);
    std::vector<int> search(const std::string &ingredient);
    std::vector<Recipe> query(const std::vector<std::string> &pantry) override;
    ~HashMap();
};

#endif // HASHMAP_H