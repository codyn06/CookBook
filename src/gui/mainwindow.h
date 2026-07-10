#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <vector>
#include <string>

#include "IngredientInput.h"
#include "StructureSelect.h"
#include "ResultsScreen.h"
#include "structures/Structure.h"
#include "structures/graph/Graph.h"
#include "structures/hashmap/HashMap.h"
#include "data/data.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const std::vector<Recipe>& recipes, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleIngredientsSubmitted(const std::vector<std::string> &ingredients);
    void handleStructureSelected(int selection);

private:
    QStackedWidget *stackedWidget;
    
    IngredientInput *inputScreen;
    StructureSelect *structureScreen;
    ResultsScreen *resultsScreen;

    std::vector<std::string> currentIngredients;
    std::vector<Recipe> allRecipes;

    Structure *graphStructure;
    Structure *hashMapStructure;
};

#endif // MAINWINDOW_H