#include <QApplication>
#include "gui/StructureSelect.h"
#include "data/data.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Load recipes (optional for now)
    //std::vector<Recipe> recipes = loadRecipes("../dataset/full_dataset.csv");

    StructureSelect window;
    window.show();

    return app.exec();
}



// #include <iostream>
// #include "data/data.h"
// int main() {
//     std::vector<Recipe> recipes = loadRecipes("../dataset/full_dataset.csv");
// }