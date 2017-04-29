#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("XPlayer"));
    resize(1024, 768);

    player_widget = new PlayerWidget(this);
    if(!setupMenuBar())
        close();

    player_widget->show();
    setCentralWidget(player_widget);
}

MainWindow::~MainWindow()
{
}

bool MainWindow::setupMenuBar()
{
    QMenuBar *menubar = new QMenuBar(this);
    QMenu *filemenu = new QMenu("File");

    QAction *file_open = filemenu->addAction(tr("Open"));
    QAction *file_exit = filemenu->addAction(tr("Exit"));
    menubar->addMenu(filemenu);

    connect(file_open, &QAction::triggered, player_widget, &PlayerWidget::openFile);
    connect(file_exit, &QAction::triggered, this, &QMainWindow::close);

    setMenuBar(menubar);
    return true;
}
