#include <QApplication>
#include <vector>
#include <string>

#include "../src/gui/mainwindow.h"
#include "../src/data/Recipe.h"
#include "../src/structures/graph/Graph.h"
#include "../src/structures/hashmap/HashMap.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::vector<Recipe> testRecipes;
    
    Recipe r1;
    r1.id = 1;
    r1.title = "Chicken Picatta";
    r1.ingredients = {"1 lb chicken", "2 lemons", "1 tbsp butter", "capers"};
    r1.ner = {"chicken", "lemon", "butter", "capers"};
    testRecipes.push_back(r1);
    
    Recipe r2;
    r2.id = 2;
    r2.title = "Chicken Parmesan";
    r2.ingredients = {"1 lb chicken", "tomato sauce", "mozzarella cheese"};
    r2.ner = {"chicken", "tomato sauce", "mozzarella"};
    testRecipes.push_back(r2);

    Recipe r3;
    r3.id = 3;
    r3.title = "Lemon Butter Pasta";
    r3.ingredients = {"pasta", "lemon", "butter", "garlic"};
    r3.ner = {"pasta", "lemon", "butter", "garlic"};
    testRecipes.push_back(r3);

    Graph testGraph(testRecipes);
    HashMap testHashMap(testRecipes);

    MainWindow mainWindow(&testGraph, &testHashMap);
    mainWindow.setWindowTitle("Test: Main Flow");
    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}