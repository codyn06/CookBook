#include "mainwindow.h"
#include <QCoreApplication>

MainWindow::MainWindow(const std::vector<Recipe>& recipes, QWidget *parent)
    : QMainWindow(parent),
      allRecipes(recipes),
      graphStructure(nullptr),
      hashMapStructure(nullptr)
{
    stackedWidget = new QStackedWidget(this);

    // Create instances of the screens, and add it to the stack widget to allow for movement between them.
    inputScreen = new IngredientInput(this);
    structureScreen = new StructureSelect(this);
    loadingScreen = new LoadingScreen(this);
    resultsScreen = new ResultsScreen(this);

    stackedWidget->addWidget(inputScreen);
    stackedWidget->addWidget(structureScreen);
    stackedWidget->addWidget(loadingScreen);
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
    stackedWidget->setCurrentIndex(2);
    QCoreApplication::processEvents();
    std::vector<RecipeMatch> matches;

    // Build the hashmap AFTER user selects it in selection screen
    // Check that its nullptr so that it does not build the data structure from scratch again
    if (selection == StructureSelect::HASHMAP)
    { 
        if (hashMapStructure == nullptr) {
            hashMapStructure = new HashMap(allRecipes);
        }
        matches = hashMapStructure->getTopN(currentIngredients, 100);
    }
    // Build the graph AFTER user selects it in selection screen
    else if (selection == StructureSelect::GRAPH)
    {
        if (graphStructure == nullptr) {
            graphStructure = new Graph(allRecipes);
        }
        matches = graphStructure->getTopN(currentIngredients, 100);
    }

    resultsScreen->setRecipes(matches);
    stackedWidget->setCurrentIndex(3);
}

void MainWindow::handleHomeRequested()
{
    stackedWidget->setCurrentIndex(0);
}