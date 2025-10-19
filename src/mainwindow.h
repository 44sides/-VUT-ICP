/*!
 * @file mainwindow.h
 * @author Josef Susík (xsusik00)
 * @author Vladyslav Tverdokhlib (xtverd01)
 * @brief Main window header
 */



#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simulation.h"

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

public slots:
    void pauseSim();
    void addRobot();
    void addObstacle();
    void Save();

private:
    Ui::MainWindow *ui;
    Simulation * simulation;
};
#endif // MAINWINDOW_H
