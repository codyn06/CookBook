#include "data.h"
// ,title,ingredients,directions,link,source,NER
// 0,No-Bake Nut Cookies,"[""1 c. firmly packed brown sugar"", ""1/2 c. evaporated milk"", ""1/2 tsp. vanilla"", ""1/2 c. broken nuts (pecans)"", ""2 Tbsp. butter or margarine"", ""3 1/2 c. bite size shredded rice biscuits""]","[""In a heavy 2-quart saucepan, mix brown sugar, nuts, evaporated milk and butter or margarine."", ""Stir over medium heat until mixture bubbles all over top."", ""Boil and stir 5 minutes more. Take off heat."", ""Stir in vanilla and cereal; mix well."", ""Using 2 teaspoons, drop and shape into 30 clusters on wax paper."", ""Let stand until firm, about 30 minutes.""]",www.cookbooks.com/Recipe-Details.aspx?id=44874,Gathered,"[""brown sugar"", ""milk"", ""vanilla"", ""nuts"", ""butter"", ""bite size shredded rice biscuits""]"

std::vector<std::string> parseStringifiedList(const std::string &listStr)
{
    std::vector<std::string> result;
    bool inQuote = false;
    char quoteChar = '\0';
    std::string currentItem = "";

    for (size_t i = 0; i < listStr.length(); ++i)
    {
        char c = listStr[i];

        if ((c == '\'' || c == '"') && (i == 0 || listStr[i - 1] != '\\'))
        {
            if (!inQuote)
            {
                inQuote = true;
                quoteChar = c;
            }
            else if (c == quoteChar)
            {
                inQuote = false;
                result.push_back(currentItem);
                currentItem = "";
            }
            else
            {
                currentItem += c;
            }
        }
        else if (inQuote)
        {
            currentItem += c;
        }
    }
    return result;
}

std::vector<std::string> parseCSVRow(const std::string &line)
{
    std::vector<std::string> result;
    std::string current = "";
    bool inQuotes = false;

    for (char c : line)
    {
        if (c == '"')
        {
            inQuotes = !inQuotes;
        }
        else if (c == ',' && !inQuotes)
        {
            result.push_back(current);
            current = "";
        }
        else
        {
            current += c;
        }
    }
    result.push_back(current);
    return result;
}

std::vector<Recipe> loadRecipes(const std::string &filename)
{
    std::vector<Recipe> recipes;

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return recipes;
    }

    recipes.reserve(2250000);

    std::string line;
    std::getline(file, line);

    size_t count = 0;

    while (std::getline(file, line))
    {
        std::vector<std::string> row = parseCSVRow(line);

        if (row.size() < 7)
            continue;

        Recipe recipe;
        try
        {
            recipe.id = std::stoi(row[0]);
        }
        catch (...)
        {
            continue;
        }

        recipe.title = row[1];
        recipe.ingredients = parseStringifiedList(row[2]);
        recipe.directions = parseStringifiedList(row[3]);
        recipe.link = row[4];
        recipe.ner = parseStringifiedList(row[6]);

        recipes.push_back(std::move(recipe));

        count++;
        if (count % 100000 == 0)
        {
            std::cout << "Loaded " << count << " recipes...\n";
        }
    }

    file.close();
    recipes.shrink_to_fit();

    std::cout << "Finished loading " << recipes.size() << " recipes successfully!\n";
    return recipes;
}