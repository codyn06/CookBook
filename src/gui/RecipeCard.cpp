#include "RecipeCard.h"
#include <QString>
#include <QStringList>

RecipeCard::RecipeCard(const RecipeMatch& match, QWidget *parent) 
    : QFrame(parent) {
    
    this->setFrameShape(QFrame::StyledPanel);
    this->setStyleSheet("RecipeCard { border: 1px solid black; border-radius: 8px; background-color: white; }");
    this->setFixedSize(220, 350); 

    setupUi(match);
}

