#ifndef PROJECT_2_STRUCTURESELECT_H
#define PROJECT_2_STRUCTURESELECT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class StructureSelect : public QWidget
{
    Q_OBJECT

public:
    explicit StructureSelect(QWidget *parent = nullptr);

    enum SelectedDS { NONE, HASHMAP, GRAPH };
    SelectedDS getSelection() const { return selection; }

    signals:
        void dataStructureChosen(SelectedDS ds);
    void nextPressed(SelectedDS ds);

private slots:
    void chooseHashMap();
    void chooseGraph();
    void goNext();

private:
    QPushButton *hashMapBtn;
    QPushButton *graphBtn;
    QPushButton *nextBtn;

    SelectedDS selection;
};

#endif
