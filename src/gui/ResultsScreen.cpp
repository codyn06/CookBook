#include "ResultsScreen.h"
#include "RecipeCard.h"

ResultsScreen::ResultsScreen(QWidget *parent) : QWidget(parent) {
    mainLayout = new QVBoxLayout(this);

    headerLabel = new QLabel("Top Recipes:", this);
    QFont headerFont = headerLabel->font();
    headerFont.setPointSize(24); 
    headerFont.setBold(true);
    headerLabel->setFont(headerFont);

    mainLayout->addWidget(headerLabel);

    cardsLayout = new QHBoxLayout();
    
    cardsLayout->setAlignment(Qt::AlignLeft); 

    mainLayout->addLayout(cardsLayout);

    mainLayout->addStretch();
}

void ResultsScreen::setRecipes(const std::vector<RecipeMatch> &matches) {
    // Clear existing cards in the case that user did a previous search
    QLayoutItem *child;
    while ((child = cardsLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget(); 
        }
        delete child; 
    }

    if (matches.empty()) {
        QLabel *noResultsLabel = new QLabel("No recipes found. Try adding or adjusting your ingredients!", this);
        
        QFont emptyFont = noResultsLabel->font();
        emptyFont.setPointSize(14);
        emptyFont.setItalic(true);
        noResultsLabel->setFont(emptyFont);
        
        noResultsLabel->setAlignment(Qt::AlignCenter);
        
        cardsLayout->addWidget(noResultsLabel);
        return; 
    }

    for (const RecipeMatch& match : matches) {
        RecipeCard *card = new RecipeCard(match, this);
        
        cardsLayout->addWidget(card);
    }
}