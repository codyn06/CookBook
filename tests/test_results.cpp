#include <QApplication>
#include <vector>
#include <string>

#include "../src/gui/ResultsScreen.h"
#include "../src/structures/Structure.h" 

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ResultsScreen results;
    results.setWindowTitle("Test: Results Screen");
    
    results.resize(1000, 450); 

    std::vector<RecipeMatch> testMatches;

    Recipe r1;
    r1.title = "Chicken Picatta";
    r1.ingredients = {"chicken", "lemon", "butter", "capers"};
    testMatches.push_back({r1, 100.0, {}}); 

    Recipe r2;
    r2.title = "Chicken Tikka Masala";
    r2.ingredients = {"chicken", "yogurt", "garam masala", "tomato puree"};
    testMatches.push_back({r2, 100.0, {}});

    Recipe r3;
    r3.title = "Chicken Parmesan";
    r3.ingredients = {"chicken", "tomato sauce", "mozzarella"};
    testMatches.push_back({r3, 90.0, {"parmesan"}});

    Recipe r4;
    r4.title = "Chicken Marsala";
    r4.ingredients = {"chicken", "marsala wine", "mushrooms"};
    testMatches.push_back({r4, 80.0, {}});

    results.setRecipes(testMatches);

    results.show();
    return app.exec();
}