#include "mainwindow.h"

MainWindow::MainWindow(Structure *graph, Structure *hashmap, QWidget *parent) 
    : QMainWindow(parent),
      graphStructure(graph),
      hashMapStructure(hashmap)
{
    stackedWidget = new QStackedWidget(this);

    inputScreen = new IngredientInput(this);
    structureScreen = new StructureSelect(this);
    resultsScreen = new ResultsScreen(this);

    stackedWidget->addWidget(inputScreen);       
    stackedWidget->addWidget(structureScreen);   
    stackedWidget->addWidget(resultsScreen);    

    setCentralWidget(stackedWidget);
    resize(800, 600); 

    connect(inputScreen, &IngredientInput::ingredientsSubmitted,
            this, &MainWindow::handleIngredientsSubmitted);

    connect(structureScreen, &StructureSelect::nextPressed,
            this, &MainWindow::handleStructureSelected);
}

void MainWindow::handleIngredientsSubmitted(const std::vector<std::string> &ingredients) {
    currentIngredients = ingredients;
    stackedWidget->setCurrentIndex(1);
}