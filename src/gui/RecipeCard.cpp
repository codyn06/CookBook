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

void RecipeCard::setupUi(const RecipeMatch& match) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    int displayScore = static_cast<int>(match.score);
    QLabel *pctLabel = new QLabel(QString::number(displayScore) + "%", this);
    pctLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
    layout->addWidget(pctLabel);

    QLabel *titleLabel = new QLabel(QString::fromStdString(match.recipe.title), this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setWordWrap(true);
    QFont titleFont = titleLabel->font();
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    layout->addWidget(titleLabel);

    QFrame *divider = new QFrame(this);
    divider->setFrameShape(QFrame::HLine);
    divider->setStyleSheet("border: 1px solid black;");
    layout->addWidget(divider);

    QLabel *ingredientsLabel = new QLabel(this);
    ingredientsLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ingredientsLabel->setWordWrap(true);
    ingredientsLabel->setTextFormat(Qt::RichText);

    QStringList presentIngredients;
    for (const auto& ing : match.recipe.ingredients) {
        presentIngredients << QString::fromStdString(ing);
    }
    
    QString ingredientsHtml = "ingredients: " + presentIngredients.join(", ") + "<br><br>";

    if (!match.missing.empty()) {
        QStringList missingList;
        for (const auto& missingIng : match.missing) {
            missingList << QString::fromStdString(missingIng);
        }
        ingredientsHtml += "<span style='color:red;'>x " + missingList.join(", ") + "</span>";
    }

    ingredientsLabel->setText(ingredientsHtml);
    layout->addWidget(ingredientsLabel);
    
    layout->addStretch();
}