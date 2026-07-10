#ifndef RESULTSSCREEN_H
#define RESULTSSCREEN_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <vector>

#include "structures/Structure.h" 

class ResultsScreen : public QWidget {
    Q_OBJECT

public:
    explicit ResultsScreen(QWidget *parent = nullptr);
    
    void setRecipes(const std::vector<RecipeMatch> &matches);

private:
    QVBoxLayout *mainLayout;   
    QLabel *headerLabel;       
    QHBoxLayout *cardsLayout;  
};

#endif // RESULTSSCREEN_H