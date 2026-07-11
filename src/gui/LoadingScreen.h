#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <QWidget>
#include <QLabel>

class LoadingScreen : public QWidget {
    Q_OBJECT

public:
    explicit LoadingScreen(QWidget *parent = nullptr);
    
private:
    QLabel *messageLabel;
};

#endif // LOADINGSCREEN_H