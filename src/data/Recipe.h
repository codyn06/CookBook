#ifndef RECIPE_H
#define RECIPE_H
#include <string>
#include <vector>


struct Recipe {
    int id;
    std::string title;
    std::vector<std::string> ingredients;
    std::vector<std::string> directions;
    std::string link;
    std::vector<std::string> ner;
};


#endif //RECIPE_H