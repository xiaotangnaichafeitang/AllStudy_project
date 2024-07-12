#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include <QDebug>
#include "../include/Game_2048/gui/qgameboard.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupUI();
    void outUp();

private:
    Ui::MainWindow *ui;
    QGameBoard *m_gameBoard;

private slots:
    void newFile() { qDebug() << "New File Action triggered"; }
    void openFile() { qDebug() << "Open File Action triggered"; }
    void saveFile() { qDebug() << "Save File Action triggered"; }
    void cut() { qDebug() << "Cut Action triggered"; }
    void copy() { qDebug() << "Copy Action triggered"; }
    void paste() { qDebug() << "Paste Action triggered"; }
    void zoomIn() { qDebug() << "Zoom In Action triggered"; }
    void zoomOut() { qDebug() << "Zoom Out Action triggered"; }
    void game_2048In();
};
#endif // MAINWINDOW_H
