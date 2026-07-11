#include "ResultsScreen.h"
#include "RecipeCard.h"
#include <QScrollArea>

ResultsScreen::ResultsScreen(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);

    // Home button that routes back to ingredient input screen
    homeButton = new QPushButton("Home", this);
    homeButton->setFixedSize(90, 35);
    connect(homeButton, &QPushButton::clicked, this, &ResultsScreen::homeRequested);

    // Top Recipes header
    headerLabel = new QLabel("Top Recipes:", this);
    QFont headerFont = headerLabel->font();
    headerFont.setPointSize(24);
    headerFont.setBold(true);
    headerLabel->setFont(headerFont);

    mainLayout->addWidget(homeButton, 0, Qt::AlignLeft);
    mainLayout->addWidget(headerLabel);

    // Scroll bar to see all recipes
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollContainer = new QWidget();

    cardsLayout = new FlowLayout(scrollContainer, 10, 10, 10);
    cardsLayout->setContentsMargins(10, 10, 10, 10);

    scrollArea->setWidget(scrollContainer);
    mainLayout->addWidget(scrollArea);
}

void ResultsScreen::setRecipes(const std::vector<RecipeMatch> &matches)
{
    QLayoutItem *child;
    // Clear the old recipe cards if needed
    while ((child = cardsLayout->takeAt(0)) != nullptr)
    {
        if (child->widget())
        {
            delete child->widget();
        }
        delete child;
    }

    // Handles case if user's ingredient input does not match to any recipes.
    if (matches.empty())
    {
        QLabel *noResultsLabel = new QLabel("No recipes found. Try adding or adjusting your ingredients!", this);

        QFont emptyFont = noResultsLabel->font();
        emptyFont.setPointSize(14);
        emptyFont.setItalic(true);
        noResultsLabel->setFont(emptyFont);

        noResultsLabel->setAlignment(Qt::AlignCenter);

        cardsLayout->addWidget(noResultsLabel);
        return;
    }

    for (const auto &match : matches)
    {
        RecipeCard *card = new RecipeCard(match, this);
        cardsLayout->addWidget(card);
    }
}