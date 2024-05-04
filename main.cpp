//#include "mainwindow.h"

#include <QApplication>
#include "simulation.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Simulation sim;
    sim.show();
    return app.exec();
}
