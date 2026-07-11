#include "LoadingScreen.h"
#include <QVBoxLayout>

LoadingScreen::LoadingScreen(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    messageLabel = new QLabel("Building data structure and querying recipes...", this);
    messageLabel->setAlignment(Qt::AlignCenter);

    QFont font = messageLabel->font();
    font.setPointSize(14);
    font.setBold(true);
    messageLabel->setFont(font);
    
    layout->addStretch();
    layout->addWidget(messageLabel);
    layout->addStretch();
    
    setLayout(layout);
}