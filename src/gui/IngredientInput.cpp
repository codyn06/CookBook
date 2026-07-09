#include "IngredientInput.h"
#include <algorithm>

IngredientInput::IngredientInput(QWidget *parent) : QWidget(parent)
{
    setupUi();
}

void IngredientInput::setupUi() {}

void IngredientInput::onAddIngredientText()
{
    std::string text = ingredientTextField->text().trimmed().toLower().toStdString();

    // Edge Cases
    if (text.empty())
    {
        return;
    }

    if (std::find(selectedIngredients.begin(), selectedIngredients.end(), text) != selectedIngredients.end())
    {
        ingredientTextField->clear();
        return;
    }

    selectedIngredients.push_back(text);
    addIngredientTag(text);
    ingredientTextField->clear();
}