#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    creatMenuBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::creatMenuBar()
{
    game_2048_Action = new QAction(tr("2048"),this);
    gameMenu = menuBar()->addMenu("游戏项目");
    gameMenu->addAction(game_2048_Action);
}
