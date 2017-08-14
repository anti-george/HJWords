#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Preprocessor *preload = new Preprocessor;
    connect(preload, SIGNAL(appendPlainText(QString)), this, SLOT(appendPlainText(QString)));
    QTimer::singleShot(0, preload, SLOT(preload()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appendPlainText(QString str)
{
    ui->plainTextEdit->appendPlainText(str);
}
