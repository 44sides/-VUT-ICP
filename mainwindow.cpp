#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)  // Initialize 'ui' using the generated class
{
    ui->setupUi(this);  // Setup the UI
    // Your additional initialization code goes here
}

MainWindow::~MainWindow()
{
    delete ui;
}
