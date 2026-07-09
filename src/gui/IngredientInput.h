#ifndef INGREDIENT_INPUT_H
#define INGREDIENT_INPUT_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include <string>

class IngredientInput : public QWidget
{
    Q_OBJECT

public:
    explicit IngredientInput(QWidget *parent = nullptr);
    std::vector<std::string> getSelectedIngredients() const;

signals:
    void ingredientsSubmitted(const std::vector<std::string> &pantry);

private slots:
    void onAddIngredientText();
    void onChipToggled(const QString &ingredient, bool checked);
    void onNextClicked();

private:
    void setupUi();
    void addChip(const QString &ingredient);
    void addIngredientToList(const std::string &ingredient);
    void removeIngredientFromList(const std::string &ingredient);

    QLineEdit *ingredientTextField;
    QPushButton *nextButton;
    QHBoxLayout *chipLayout;
    QVBoxLayout *selectedListLayout;

    std::vector<std::string> selectedIngredients;
};

#endif // INGREDIENT_INPUT_H