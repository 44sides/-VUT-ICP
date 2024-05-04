#ifndef SIMULATION_H
#define SIMULATION_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "robot.h"
#include "userRobot.h"
#include "obstacle.h"

class Simulation : public QGraphicsView
{
    Q_OBJECT

public:
    Simulation(QWidget *parent = nullptr);
    void loadFromJson(const QString& filename);
    void togglePause();

private slots:
    void advanceScene();

private:
    QGraphicsScene *scene;
    bool isPaused = false;

};

#endif // SIMULATION_H
