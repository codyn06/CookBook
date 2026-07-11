#include "StructureSelect.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

StructureSelect::StructureSelect(QWidget *parent)
    : QWidget(parent), selection(NONE)
{
    hashMapBtn = new QPushButton("Hash Map");
    graphBtn = new QPushButton("Graph");
    nextBtn = new QPushButton("Next");

    hashMapBtn->setCheckable(true);
    graphBtn->setCheckable(true);

    hashMapBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    graphBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    hashMapBtn->setMinimumHeight(160);
    graphBtn->setMinimumHeight(160);

    QHBoxLayout *buttonRow = new QHBoxLayout;
    buttonRow->setSpacing(12);
    buttonRow->addWidget(hashMapBtn, 1);
    buttonRow->addWidget(graphBtn, 1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(12);
    layout->addLayout(buttonRow);
    layout->addWidget(nextBtn);

    setLayout(layout);

    connect(hashMapBtn, &QPushButton::clicked, this, &StructureSelect::chooseHashMap);
    connect(graphBtn, &QPushButton::clicked, this, &StructureSelect::chooseGraph);
    connect(nextBtn, &QPushButton::clicked, this, &StructureSelect::goNext);
}

void StructureSelect::chooseHashMap()
{
    selection = HASHMAP;
    hashMapBtn->setChecked(true);
    graphBtn->setChecked(false);
    emit dataStructureChosen(selection);
}

void StructureSelect::chooseGraph()
{
    selection = GRAPH;
    graphBtn->setChecked(true);
    hashMapBtn->setChecked(false);
    emit dataStructureChosen(selection);
}

void StructureSelect::goNext()
{
    if (selection == NONE)
    {
        return;
    }

    emit nextPressed(selection);
}
