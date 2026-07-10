#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <vector>
#include <string>

#include "IngredientInput.h"
#include "StructureSelect.h"
#include "ResultsScreen.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void handleIngredientsSubmitted(const std::vector<std::string> &ingredients);
    void handleStructureSelected(int selection);

private:
    QStackedWidget *stackedWidget;
    
    IngredientInput *inputScreen;
    StructureSelect *structureScreen;
    ResultsScreen *resultsScreen;

    std::vector<std::string> currentIngredients;
};

#endif // MAINWINDOW_H