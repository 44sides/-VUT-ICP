//#include "mainwindow.h"

#include <QApplication>
#include "simulation.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Simulation sim;
    sim.showFullScreen();
    return app.exec();
}
