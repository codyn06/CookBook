#ifndef INGREDIENTINPUT_H
#define INGREDIENTINPUT_H

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
    void onNextClicked();

private:
    void setupUi();
    void addIngredientTag(const std::string &ingredient);
    void removeIngredientTag(const std::string &ingredient);

    QLineEdit *ingredientTextField;
    QPushButton *nextButton;
    QVBoxLayout *tagLayout;

    std::vector<std::string> selectedIngredients;
};

#endif // INGREDIENT_INPUT_H