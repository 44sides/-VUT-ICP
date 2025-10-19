/*!
 * @file main.cpp
 * @author Josef Susík (xsusik00)
 * @author Vladyslav Tverdokhlib (xtverd01)
 * @brief Main file
 */

#include "mainwindow.h"
#include <QApplication>

/**
 * @brief The main function of the application, Qt generated.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return The exit status of the application.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
