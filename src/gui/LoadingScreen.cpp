#include "LoadingScreen.h"
#include <QVBoxLayout>

LoadingScreen::LoadingScreen(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    messageLabel = new QLabel("Building data structure and querying recipes...", this);
    messageLabel->setAlignment(Qt::AlignCenter);
    
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 0); // 0,0 range makes the bar bounce back and forth automatically
    progressBar->setTextVisible(false);
    
    layout->addStretch();
    layout->addWidget(messageLabel);
    layout->addWidget(progressBar);
    layout->addStretch();
    
    setLayout(layout);
}