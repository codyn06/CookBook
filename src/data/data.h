#ifndef DATA_H
#define DATA_H

#include "rapidcsv.h"
#include "Recipe.h"

std::vector<std::string> parseStringifiedList(const std::string &listString);
std::vector<std::string> parseCSVRow(const std::string &line);
std::vector<Recipe> loadRecipes(const std::string &filename);

#endif // DATA_H