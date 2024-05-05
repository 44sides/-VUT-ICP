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

class Simulation : public QGraphicsScene
{
    Q_OBJECT

public:
    Simulation(QObject *parent = nullptr, QString path = nullptr);
    void loadFromJson(const QString& filename);
    void togglePause();
    void addRobot(qreal x, qreal y, qreal angle, qreal speed, qreal turnAngle, const QString& rotationDirection, const QColor& color, qreal detectionDistance);
    void addObstacle(qreal x, qreal y, qreal size, qreal rotation);
    void saveToJson(const QString& filename);

    bool isPaused = true;

private slots:
    void advanceScene();



private:
    //QGraphicsScene *scene;
};

#endif // SIMULATION_H
