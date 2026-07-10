#include <QApplication>
#include <iostream>
#include "../src/gui/ingredientinput.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    IngredientInput input;
    input.setWindowTitle("Test: Ingredient Input");
    input.resize(400, 300);

    // Print pantry
    QObject::connect(&input, &IngredientInput::ingredientsSubmitted,
                     [](const std::vector<std::string> &pantry)
                     {
                         for (const auto &ing : pantry)
                         {
                             std::cout << "\"" << ing << "\" ";
                         }
                     });

    input.show();
    return app.exec();
}