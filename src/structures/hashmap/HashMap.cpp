#include "HashMap.h"

#include <unordered_set>
#include <queue>

HashMap::HashMap(int cap) : capacity(cap), size(0)
{
    table.resize(cap, nullptr);
}

HashMap::HashMap(const std::vector<Recipe> &recipes)
{
    // Large prime to mitigate collisions in our hash function.
    capacity = 100003;
    size = 0;
    table.resize(capacity, nullptr);

    for (const auto &r : recipes)
    {
        recipeLookup[r.id] = r;
        for (const auto &i : r.ner)
        {
            insert(i, r.id);
        }
    }
}

std::vector<RecipeMatch> HashMap::query(const std::vector<std::string> &pantry)
{
    std::unordered_map<int, int> matchCounts;

    for (const auto &pantryIng : pantry)
    {
        std::vector<int> ids = search(pantryIng);
        for (int recipeId : ids)
        {
            matchCounts[recipeId]++;
        }
    }

    std::vector<RecipeMatch> results;
    std::unordered_set<std::string> pantrySet(pantry.begin(), pantry.end());

    for (const auto &pair : matchCounts)
    {
        int recipeId = pair.first;
        int matches = pair.second;

        const Recipe &r = recipeLookup.at(recipeId);

        int totalIngredients = r.ner.size();
        double score = static_cast<double>(matches) / totalIngredients;

        std::vector<std::string> missing;
        for (const auto &ing : r.ner)
        {
            if (pantrySet.find(ing) == pantrySet.end())
            {
                missing.push_back(ing);
            }
        }

        results.push_back({r, score, missing});
    }

    return results;
}

void HashMap::insert(const std::string &ingredient, int recipeId)
{
    int i = hashFunction(ingredient);

    HashNode *curr = table[i];
    while (curr != nullptr)
    {
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

// Hash function: Multiply the current hash by 31 and add the ASCII value of the char.
int HashMap::hashFunction(const std::string &ingredient)
{

    unsigned int hash_value = 0;
    for (char c : ingredient)
    {
        hash_value = (hash_value * 31) + c;
    }
    return hash_value % capacity;
}

std::vector<RecipeMatch> HashMap::getTopN(const std::vector<std::string> &pantry, int N)
{
    std::vector<RecipeMatch> matches = query(pantry);

    // Lambda that compares the scores
    auto cmp = [](const RecipeMatch &a, const RecipeMatch &b)
    {
        return a.score < b.score;
    };

    std::priority_queue<
        RecipeMatch,
        std::vector<RecipeMatch>,
        decltype(cmp)>
        pq(cmp);

    for (const auto &m : matches)
    {
        pq.push(m);
    }

    std::vector<RecipeMatch> topN;
    for (int i = 0; i < N && !pq.empty(); i++)
    {
        topN.push_back(pq.top());
        pq.pop();
    }

    return topN;
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
