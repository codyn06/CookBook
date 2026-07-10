#ifndef RECIPECARD_H
#define RECIPECARD_H

#include <QLayout>
#include "data/Recipe.h" 

class RecipeCard : public QFrame {
    Q_OBJECT

public:
    explicit RecipeCard(const Recipe& recipe, QWidget *parent = nullptr);

private:
    void setupUi(const Recipe& recipe);
};

#endif // RECIPECARD_H