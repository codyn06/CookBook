#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
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