#ifndef HASHMAP_H
#define HASHMAP_H

#include "../Structure.h"
#include <unordered_map>

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

    std::unordered_map<int, Recipe> recipeLookup;
    int hashFunction(const std::string &ingredient);

public:
    HashMap(const std::vector<Recipe> &recipes);
    HashMap(int cap);
    void insert(const std::string &ingredient, int recipeId);
    std::vector<int> search(const std::string &ingredient);
    std::vector<RecipeMatch> query(const std::vector<std::string> &pantry) override;
    ~HashMap();
};

#endif // HASHMAP_H
