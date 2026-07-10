#include <QApplication>
#include "gui/StructureSelect.h"
#include "data/data.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::vector<Recipe> recipes = loadRecipes("../dataset/full_dataset.csv");

    return app.exec();
}



