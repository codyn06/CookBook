#include "mainwindow.h"

MainWindow::MainWindow(const std::vector<Recipe>& recipes, QWidget *parent)
    : QMainWindow(parent),
      allRecipes(recipes),
      graphStructure(nullptr),
      hashMapStructure(nullptr)
{
    stackedWidget = new QStackedWidget(this);

    inputScreen = new IngredientInput(this);
    structureScreen = new StructureSelect(this);
    resultsScreen = new ResultsScreen(this);

    stackedWidget->addWidget(inputScreen);
    stackedWidget->addWidget(structureScreen);
    stackedWidget->addWidget(resultsScreen);

    setCentralWidget(stackedWidget);
    resize(960, 800); 

    connect(inputScreen, &IngredientInput::ingredientsSubmitted,
            this, &MainWindow::handleIngredientsSubmitted);

    connect(structureScreen, &StructureSelect::nextPressed,
            this, &MainWindow::handleStructureSelected);
    connect(resultsScreen, &ResultsScreen::homeRequested,
            this, &MainWindow::handleHomeRequested);
}

MainWindow::~MainWindow() {
    delete graphStructure;
    delete hashMapStructure;
}

void MainWindow::handleIngredientsSubmitted(const std::vector<std::string> &ingredients)
{
    currentIngredients = ingredients;
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::handleStructureSelected(int selection)
{
    std::vector<RecipeMatch> matches;

    if (selection == StructureSelect::HASHMAP)
    { 
        if (hashMapStructure == nullptr) {
            hashMapStructure = new HashMap(allRecipes);
        }
        matches = hashMapStructure->getTopN(currentIngredients, 100);
    }
    else if (selection == StructureSelect::GRAPH)
    {
        if (graphStructure == nullptr) {
            graphStructure = new Graph(allRecipes);
        }
        matches = graphStructure->getTopN(currentIngredients, 100);
    }

    resultsScreen->setRecipes(matches);
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::handleHomeRequested()
{
    stackedWidget->setCurrentIndex(0);
}