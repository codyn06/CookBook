#include "ResultsScreen.h"
#include "RecipeCard.h"
#include <QScrollArea>

ResultsScreen::ResultsScreen(QWidget *parent) : QWidget(parent) {
    this->setFixedSize(960,800);
    
    mainLayout = new QVBoxLayout(this);

    headerLabel = new QLabel("Top Recipes:", this);
    QFont headerFont = headerLabel->font();
    headerFont.setPointSize(24); 
    headerFont.setBold(true);
    headerLabel->setFont(headerFont);

    mainLayout->addWidget(headerLabel);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true); 
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); 
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setFrameShape(QFrame::NoFrame); 

    QWidget *scrollContainer = new QWidget();

    cardsLayout = new QGridLayout(scrollContainer);
    cardsLayout->setSpacing(10); 
    cardsLayout->setContentsMargins(10, 10, 10, 10);
    cardsLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft); 

    scrollArea->setWidget(scrollContainer);
    mainLayout->addWidget(scrollArea);
}

void ResultsScreen::setRecipes(const std::vector<RecipeMatch> &matches) {
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
        
        cardsLayout->addWidget(noResultsLabel, 0, 0); 
        return; 
    }

    int columns = 4; 
    for (size_t i = 0; i < matches.size(); ++i) {
        RecipeCard *card = new RecipeCard(matches[i], this);
        
        int row = i / columns; 
        int col = i % columns; 
        
        cardsLayout->addWidget(card, row, col);
    }
}