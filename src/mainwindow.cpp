#include "mainwindow.h"
#include "./ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //增加全局支持 Uicode 识别支持，解决中文乱码问题
    QTextCodec *code = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForLocale(code);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
