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
    r1.ner = {"chicken", "lemon", "butter", "capers"};
    testRecipes.push_back(r1);
    
    Recipe r2;
    r2.id = 2;
    r2.title = "Chicken Parmesan";
    r2.ner = {"chicken", "tomato sauce", "mozzarella"};
    testRecipes.push_back(r2);

    Recipe r3;
    r3.id = 3;
    r3.title = "Lemon Butter Pasta";
    r3.ner = {"pasta", "lemon", "butter", "garlic"};
    testRecipes.push_back(r3);

    Recipe r4;
    r4.id = 4;
    r4.title = "Beef Stew";
    r4.ner = {"beef", "potatoes", "carrots", "beef broth"};
    testRecipes.push_back(r4);

    Recipe r5;
    r5.id = 5;
    r5.title = "Caprese Salad";
    r5.ner = {"mozzarella", "tomatoes", "basil", "balsamic vinegar"};
    testRecipes.push_back(r5);

    Recipe r6;
    r6.id = 6;
    r6.title = "Shrimp Scampi";
    r6.ner = {"shrimp", "garlic", "butter", "white wine", "pasta"};
    testRecipes.push_back(r6);

    Recipe r7;
    r7.id = 7;
    r7.title = "Avocado Toast";
    r7.ner = {"bread", "avocado", "salt", "pepper", "egg"};
    testRecipes.push_back(r7);

    Recipe r8;
    r8.id = 8;
    r8.title = "Classic Cheeseburger";
    r8.ner = {"ground beef", "cheese", "hamburger bun", "lettuce", "tomato"};
    testRecipes.push_back(r8);

    MainWindow mainWindow(testRecipes);
    mainWindow.setWindowTitle("Test: Main Flow");
    mainWindow.setFixedSize(960, 800);
    mainWindow.show();

    return app.exec();
}