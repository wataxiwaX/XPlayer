#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "playerwidget.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool setupMenuBar();

    PlayerWidget *player_widget;
};

#endif // MAINWINDOW_H
