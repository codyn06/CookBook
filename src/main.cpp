#include <QApplication>

#include "gui/mainwindow.h"
#include "data/data.h"

#include "structures/graph/Graph.h"
#include "structures/hashmap/HashMap.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::vector<Recipe> recipes = loadRecipes("../dataset/full_dataset.csv");

    Graph graph(recipes);
    HashMap hashmap(recipes);

    MainWindow mainWindow(&graph, &hashmap);
    mainWindow.setWindowTitle("CookBook");
    mainWindow.show();

    return app.exec();
}



