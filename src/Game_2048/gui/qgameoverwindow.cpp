#include "../include/Game_2048/gui/qgameoverwindow.h"
#include "../include/Game_2048/gui/qresetbutton.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QResizeEvent>

QGameOverWindow::QGameOverWindow(QWidget *parent) :
    QWidget(parent)
{
    // 设置游戏结束窗口的背景颜色为浅米色、游戏结束窗口的固定大小为425x205像素
    setStyleSheet("QGameOverWindow { background: rgb(237,224,200); }");
    setFixedSize(425,205);
    // 创建垂直布局管理器，并将其应用于当前窗口
    QVBoxLayout *layout = new QVBoxLayout(this);
    // 创建显示"Game Over!"文本的标签，并设置样式为黑色字体，粗体，字号40pt
    QLabel* gameover = new QLabel("Game Over!", this);
    gameover->setStyleSheet("QLabel { color: rgb(119,110,101); font: 40pt; font: bold;} ");
    // 创建重置按钮
    reset = new QResetButton(this);
    reset->setFixedHeight(50);
    reset->setFixedWidth(100);
    // 将游戏结束标签添加到布局中，并居中显示
    layout->insertWidget(0,gameover,0,Qt::AlignCenter);
    // 将重置按钮添加到布局中，并居中显示
    layout->insertWidget(1,reset,0,Qt::AlignCenter);
}

QResetButton* QGameOverWindow::getResetBtn() const
{
    return reset;
}
