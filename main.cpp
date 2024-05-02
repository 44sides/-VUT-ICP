#include "mainwindow.h"
#include "robot.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Robot robot(100, 100);
    MainWindow w;
    w.setCentralWidget(&robot);
    w.setGeometry(100, 100, 400, 300); // Set the window geometry
    w.show();
    return a.exec();
}
