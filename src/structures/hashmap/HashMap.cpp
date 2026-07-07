#include "HashMap.h"
HashMap::HashMap(int cap = 100003) : capacity(cap), size(0)
{
    table.resize(cap, nullptr);
}
HashMap::HashMap(const std::vector<Recipe> &recipes)
{
    for (const auto &r : recipes)
    {
        for (const auto &i : r.ner)
        {
            insert(i, r.id);
        }
    }
}

void HashMap::insert(const std::string &ingredient, int recipeId)
{
    int i = hashFunction(ingredient);

    HashNode *curr = table[i];
    while (curr != nullptr)
    {
        // Ingredient already exists -> append to Id tor ecipe list and return
        if (curr->ingredient == ingredient)
        {
            curr->recipeIds.push_back(recipeId);
            return;
        }
        curr = curr->next;
    }

    HashNode *new_node = new HashNode(ingredient);
    new_node->recipeIds.push_back(recipeId);

    new_node->next = table[i];
    table[i] = new_node;
    size++;
}

std::vector<int> HashMap::search(const std::string &ingredient)
{
    int i = hashFunction(ingredient);

    HashNode *curr = table[i];

    while (curr != nullptr)
    {
        if (curr->ingredient == ingredient)
        {
            return curr->recipeIds;
        }
        curr = curr->next;
    }
    return std::vector<int>{};
}

int HashMap::hashFunction(const std::string &ingredient)
{

    unsigned int hash_value = 0;
    // Hash value = multiply current hash value by 31 (base 31) and add the ASCII value of the char in the string
    for (char c : ingredient)
    {
        hash_value = (hash_value * 31) + c;
    }
    return hash_value % capacity;
}

HashMap::~HashMap()
{
    for (int i = 0; i < capacity; i++)
    {
        HashNode *curr = table[i];

        while (curr != nullptr)
        {
            HashNode *next = curr->next;
            delete curr;
            curr = next;
        }
        table[i] = nullptr;
    }
}

std::vector<Recipe> HashMap::query(const std::vector<std::string> &pantry)
{
    return {};
}