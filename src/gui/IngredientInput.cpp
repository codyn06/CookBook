#include "IngredientInput.h"
#include <algorithm>

IngredientInput::IngredientInput(QWidget *parent) : QWidget(parent)
{
    setupUi();
}

void IngredientInput::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    ingredientTextField = new QLineEdit(this);
    ingredientTextField->setPlaceholderText("(enter ingredients here...)");
    mainLayout->addWidget(ingredientTextField);

    // Enter pressed -> call onAddIngredientText()
    connect(ingredientTextField, &QLineEdit::returnPressed,
            this, &IngredientInput::onAddIngredientText);

    tagLayout = new FlowLayout();
    mainLayout->addLayout(tagLayout);

    mainLayout->addStretch();

    nextButton = new QPushButton("Next", this);
    connect(nextButton, &QPushButton::clicked, this, &IngredientInput::onNextClicked);
    mainLayout->addWidget(nextButton);
}

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

void IngredientInput::addIngredientTag(const std::string &ingredient)
{
    QPushButton *tag = new QPushButton(QString::fromStdString(ingredient), this);
    tag->setProperty("ingredient", QString::fromStdString(ingredient)); // store name on the widget

    connect(tag, &QPushButton::clicked, this, [this, tag, ingredient]()
            {
                removeIngredientTag(ingredient);
                tagLayout->removeWidget(tag);
                tag->deleteLater(); // safely destroy the button
            });

    tagLayout->addWidget(tag);
}

void IngredientInput::removeIngredientTag(const std::string &ingredient)
{
    selectedIngredients.erase(
        std::remove(selectedIngredients.begin(), selectedIngredients.end(), ingredient),
        selectedIngredients.end());
}

void IngredientInput::onNextClicked()
{
    if (!selectedIngredients.empty())
    {
        emit ingredientsSubmitted(selectedIngredients);
    }
}

std::vector<std::string> IngredientInput::getSelectedIngredients() const
{
    return selectedIngredients;
}