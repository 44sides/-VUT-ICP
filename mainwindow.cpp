
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simulation.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ICP 2023/2024 - Robot simulation");

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    auto pathToFile = dialog.getOpenFileName(this, tr("Open JSON file"), qApp->applicationDirPath(), tr("JSON File (*.json)"));
    simulation = new Simulation(ui->graphicsView, pathToFile);
    ui->graphicsView->setScene(simulation);
    ui->playPauseButton->setText("Play");
    connect( ui->playPauseButton, SIGNAL(clicked(bool)), this, SLOT(pauseSim()));
    connect( ui->addRobotButton, SIGNAL(clicked(bool)), this, SLOT(addRobot()));
    connect( ui->addObstacle, SIGNAL(clicked(bool)), this, SLOT(addObstacle()));
    connect( ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(Save()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pauseSim()
{
    if (simulation->isPaused == true) {
        ui->playPauseButton->setText("Pause");
    } else {
        ui->playPauseButton->setText("Play");
    }
    simulation->togglePause();
}

void MainWindow::addRobot()
{
    qreal x = ui->xLineEdit->text().toDouble();
    qreal y = ui->yLineEdit->text().toDouble();
    qreal angle = ui->angleLineEdit->text().toDouble();
    qreal speed = ui->speedLineEdit->text().toDouble();
    qreal turnAngle = ui->turnAngleLineEdit->text().toDouble();
    QString rotationDirection = ui->rotationDirectionLineEdit->text();
    QColor color(ui->colorLineEdit->text());
    qreal detectionDistance = ui->detectionDistanceLineEdit->text().toDouble();

    simulation->addRobot(x, y, angle, speed, turnAngle, rotationDirection, color, detectionDistance);
}


void MainWindow::addObstacle()
{
    qreal x = ui->xObstacle->text().toDouble();
    qreal y = ui->yObstacle->text().toDouble();
    qreal size = ui->obsSize->text().toDouble();
    qreal rotation = ui->obsRotation->text().toDouble();

    simulation->addObstacle(x, y, size, rotation);

}

void MainWindow::Save()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    auto pathToFile = dialog.getOpenFileName(this, tr("Open JSON file"), qApp->applicationDirPath(), tr("JSON File (*.json)"));
    if (!pathToFile.isEmpty()) {
        simulation->saveToJson(pathToFile);
    }
}
