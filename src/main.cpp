#include "mainwindow.h"

#include <QApplication>
#include "../include/Game_2048/gui/qgameboard.h"

int main(int argc, char *argv[])
{
    //test2
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QGameBoard board;
    board.show();

    return a.exec();
}
