#ifndef RESULTSSCREEN_H
#define RESULTSSCREEN_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>
#include <vector>

#include "structures/Structure.h" 

class ResultsScreen : public QWidget {
    Q_OBJECT

public:
    explicit ResultsScreen(QWidget *parent = nullptr);
    
    void setRecipes(const std::vector<RecipeMatch> &matches);

signals:
    void homeRequested();

private:
    QVBoxLayout *mainLayout;   
    QLabel *headerLabel;
    QPushButton *homeButton;
    QGridLayout *cardsLayout;  
};

#endif // RESULTSSCREEN_H