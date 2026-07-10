#ifndef RECIPECARD_H
#define RECIPECARD_H

#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include "structures/Structure.h" 

class RecipeCard : public QFrame {
    Q_OBJECT

public:
    explicit RecipeCard(const RecipeMatch& match, QWidget *parent = nullptr);
private:
    void setupUi(const RecipeMatch& match);
};

#endif // RECIPECARD_H