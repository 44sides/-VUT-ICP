#include "mainwindow.h"
#include "robot.h"
#include "obstacle.h"

#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    Robot robot(50, 100.1, 100.1);
    Obstacle obstacle(50, 300, 300);

    w.setGeometry(100, 100, 1400, 700);

    robot.setParent(&w);
    robot.show();

    // Debugging position output
    qDebug() << "Position: " << robot.getPosition();

    obstacle.setParent(&w);
    obstacle.show();

    w.show();

    return a.exec();
}
