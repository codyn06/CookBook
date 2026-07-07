#include "data.h"
// ,title,ingredients,directions,link,source,NER
// 0,No-Bake Nut Cookies,"[""1 c. firmly packed brown sugar"", ""1/2 c. evaporated milk"", ""1/2 tsp. vanilla"", ""1/2 c. broken nuts (pecans)"", ""2 Tbsp. butter or margarine"", ""3 1/2 c. bite size shredded rice biscuits""]","[""In a heavy 2-quart saucepan, mix brown sugar, nuts, evaporated milk and butter or margarine."", ""Stir over medium heat until mixture bubbles all over top."", ""Boil and stir 5 minutes more. Take off heat."", ""Stir in vanilla and cereal; mix well."", ""Using 2 teaspoons, drop and shape into 30 clusters on wax paper."", ""Let stand until firm, about 30 minutes.""]",www.cookbooks.com/Recipe-Details.aspx?id=44874,Gathered,"[""brown sugar"", ""milk"", ""vanilla"", ""nuts"", ""butter"", ""bite size shredded rice biscuits""]"

std::vector<std::string> parseStringifiedList(const std::string& listStr) {
    std::vector<std::string> result;
    bool inQuote = false;
    char quoteChar = '\0';
    std::string currentItem = "";
    
    for (size_t i = 0; i < listStr.length(); ++i) {
        char c = listStr[i];
        
        if ((c == '\'' || c == '"') && (i == 0 || listStr[i-1] != '\\')) {
            if (!inQuote) {
                inQuote = true;
                quoteChar = c; 
            } else if (c == quoteChar) {
                inQuote = false;
                result.push_back(currentItem);
                currentItem = ""; 
            } else {
                currentItem += c;
            }
        } else if (inQuote) {
            currentItem += c;
        }
    }
    return result;
}

std::vector<Recipe> loadRecipes(const std::string& filename) {
    std::vector<Recipe> recipes;

    try {
        rapidcsv::Document doc(filename, rapidcsv::LabelParams(0, -1));

        size_t row_count = doc.GetRowCount();
        recipes.reserve(row_count);

        for (size_t i = 0; i < row_count; ++i) {
            Recipe recipe;

            recipe.id = std::stoi(doc.GetCell<std::string>(0, i));
            recipe.title = doc.GetCell<std::string>("title", i);
            recipe.link = doc.GetCell<std::string>("link", i);

            std::string ingredientsStr = doc.GetCell<std::string>("ingredients", i);
            recipe.ingredients = parseStringifiedList(ingredientsStr);

            std::string directionsStr = doc.GetCell<std::string>("directions", i);
            recipe.directions = parseStringifiedList(directionsStr);

            std::string nerStr = doc.GetCell<std::string>("NER", i);
            recipe.ner = parseStringifiedList(nerStr);

            recipes.push_back(std::move(recipe));
        }


    }

    catch (const std::exception& e) {
        std::cerr << "Error loading recipes from file: " << e.what() << std::endl;
    }

    return recipes;
}