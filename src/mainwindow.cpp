﻿#include "mainwindow.h"
#include "./ui/ui_mainwindow.h"
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //增加全局支持 Uicode 识别支持，解决中文乱码问题
    QTextCodec *code = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForLocale(code);
    ui->setupUi(this);
    outUp();
    setupUI();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    // 创建文件菜单
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAct);

    QAction *openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(openAct);

    QAction *saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the current file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);
    fileMenu->addAction(saveAct);

    fileMenu->addSeparator();

    QAction *exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, qApp, &QApplication::quit);
    fileMenu->addAction(exitAct);

    // 创建编辑菜单
    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

    QAction *cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    connect(cutAct, &QAction::triggered, this, &MainWindow::cut);
    editMenu->addAction(cutAct);

    QAction *copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    connect(copyAct, &QAction::triggered, this, &MainWindow::copy);
    editMenu->addAction(copyAct);

    QAction *pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);
    editMenu->addAction(pasteAct);

    // 创建视图菜单
    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));

    QAction *zoomInAct = new QAction(QIcon(":/images/zoomin.png"), tr("Zoom &In"), this);
    zoomInAct->setShortcuts(QKeySequence::ZoomIn);
    zoomInAct->setStatusTip(tr("Zoom in the document"));
    connect(zoomInAct, &QAction::triggered, this, &MainWindow::zoomIn);
    viewMenu->addAction(zoomInAct);

    QAction *zoomOutAct = new QAction(QIcon(":/images/zoomout.png"), tr("Zoom &Out"), this);
    zoomOutAct->setShortcuts(QKeySequence::ZoomOut);
    zoomOutAct->setStatusTip(tr("Zoom out the document"));
    connect(zoomOutAct, &QAction::triggered, this, &MainWindow::zoomOut);
    viewMenu->addAction(zoomOutAct);
}

void MainWindow::outUp()
{
    // 创建工具栏
    QToolBar *toolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolBar);

    // 添加文件菜单动作
    QAction *newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    toolBar->addAction(newAct);

    QAction *openAct = new QAction(QIcon(":/images/open.png"), tr("&Open"), this);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);
    toolBar->addAction(openAct);

    QAction *saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setStatusTip(tr("Save the current file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);
    toolBar->addAction(saveAct);

    // 添加编辑菜单动作
    QAction *cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    connect(cutAct, &QAction::triggered, this, &MainWindow::cut);
    toolBar->addAction(cutAct);

    QAction *copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    connect(copyAct, &QAction::triggered, this, &MainWindow::copy);
    toolBar->addAction(copyAct);

    QAction *pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);
    toolBar->addAction(pasteAct);

    // 添加视图菜单动作
    QAction *zoomInAct = new QAction(QIcon(":/images/zoomin.png"), tr("Zoom &In"), this);
    zoomInAct->setStatusTip(tr("Zoom in the document"));
    connect(zoomInAct, &QAction::triggered, this, &MainWindow::zoomIn);
    toolBar->addAction(zoomInAct);

    QAction *zoomOutAct = new QAction(QIcon(":/images/zoomout.png"), tr("Zoom &Out"), this);
    zoomOutAct->setStatusTip(tr("Zoom out the document"));
    connect(zoomOutAct, &QAction::triggered, this, &MainWindow::zoomOut);
    toolBar->addAction(zoomOutAct);

    // 将工具栏添加到主窗口
    addToolBar(Qt::TopToolBarArea, toolBar);
}

