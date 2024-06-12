#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>

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
    QMenu *gameMenu;
    QMenu *toolMenu;

    QAction *game_2048_Action;

private:
    Ui::MainWindow *ui;
    void creatMenuBar();

};
#endif // MAINWINDOW_H
