#include <QApplication>
#include <QDebug>

#include "../src/gui/StructureSelect.h" 

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    StructureSelect structSelect;
    structSelect.setWindowTitle("Test: Structure Select");
    
    structSelect.resize(400, 150); 

    QObject::connect(&structSelect, &StructureSelect::dataStructureChosen, [](int selection) {
        qDebug() << "Signal dataStructureChosen emitted! Current selection enum value:" << selection;
    });

    QObject::connect(&structSelect, &StructureSelect::nextPressed, [](int selection) {
        qDebug() << "Signal nextPressed emitted! Proceeding with selection enum value:" << selection;
    });

    structSelect.show();
    return app.exec();
}