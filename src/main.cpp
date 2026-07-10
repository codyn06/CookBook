#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>

#include "gui/mainwindow.h"
#include "data/data.h"

#include "structures/graph/Graph.h"
#include "structures/hashmap/HashMap.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPixmap pixmap(500, 300);
    pixmap.fill(Qt::white);
    
    QSplashScreen splash(pixmap);
    
    splash.show();
    splash.showMessage("Loading Recipes... Please wait.", Qt::AlignCenter, Qt::black);
    
    app.processEvents();

    std::vector<Recipe> recipes = loadRecipes("../dataset/full_dataset.csv");

    Graph graph(recipes);
    HashMap hashmap(recipes);

    MainWindow mainWindow(&graph, &hashmap);
    mainWindow.setWindowTitle("CookBook");

    splash.finish(&mainWindow);
    mainWindow.show();

    return app.exec();
}



