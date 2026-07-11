#include "RecipeCard.h"
#include <QString>
#include <QStringList>

// RecipeCard constructor: takes in a RecipeMatch object and builds the recipe card.
RecipeCard::RecipeCard(const RecipeMatch &match, QWidget *parent)
    : QFrame(parent)
{

    this->setFrameShape(QFrame::StyledPanel);
    this->setStyleSheet(
        "RecipeCard { border: 1px solid black; border-radius: 8px; background-color: white; }"
        "QLabel { color: black; }");
    this->setFixedSize(220, 350);

    setupUi(match);
}

void RecipeCard::setupUi(const RecipeMatch &match)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Match score of recipe
    int displayScore = static_cast<int>(match.score * 100.0);
    QLabel *pctLabel = new QLabel(QString::number(displayScore) + "%", this);
    pctLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
    layout->addWidget(pctLabel);

    // Recipe title
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

    // Ingredient list
    QStringList presentIngredients;
    for (const auto &ing : match.recipe.ner)
    {
        presentIngredients << QString::fromStdString(ing);
    }

    QString ingredientsHtml = "ingredients: " + presentIngredients.join(", ") + "<br><br>";

    // User's missing ingredients.
    if (!match.missing.empty())
    {
        QStringList missingList;
        for (const auto &missingIng : match.missing)
        {
            missingList << QString::fromStdString(missingIng);
        }
        ingredientsHtml += "<span style='color:red;'>x " + missingList.join(", ") + "</span>";
    }

    ingredientsLabel->setText(ingredientsHtml);
    layout->addWidget(ingredientsLabel);

    layout->addStretch();
}