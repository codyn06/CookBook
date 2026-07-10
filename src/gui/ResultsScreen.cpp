#include "ResultsScreen.h"
#include "RecipeCard.h"

ResultsScreen::ResultsScreen(QWidget *parent) : QWidget(parent) {
    mainLayout = new QVBoxLayout(this);

    headerLabel = new QLabel("Top Recipes:", this);
    QFont headerFont = headerLabel->font();
    headerFont.setPointSize(24); // Make it prominent like the wireframe
    headerFont.setBold(true);
    headerLabel->setFont(headerFont);

    mainLayout->addWidget(headerLabel);

    cardsLayout = new QHBoxLayout();
    
    cardsLayout->setAlignment(Qt::AlignLeft); 

    mainLayout->addLayout(cardsLayout);

    mainLayout->addStretch();
}