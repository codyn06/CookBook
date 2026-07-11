#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>

class LoadingScreen : public QWidget {
    Q_OBJECT

public:
    explicit LoadingScreen(QWidget *parent = nullptr);
    
private:
    QLabel *messageLabel;
    QProgressBar *progressBar;
};

#endif // LOADINGSCREEN_H