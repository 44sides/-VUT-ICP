#include <QPushButton>
#include "simulation.h"
#include "interface.h"

#include <QDebug>

Simulation::Simulation(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
    QString projectDir = QCoreApplication::applicationDirPath();
    QString jsonFilePath = projectDir + "/../../icp.json";
    loadFromJson(jsonFilePath);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Simulation::advanceScene);

    Interface(this);

    timer->start(1000 / 60);
}

void Simulation::loadFromJson(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open JSON file.");
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull()) {
        qWarning("Failed to create JSON document.");
        return;
    }

    QJsonObject root = doc.object();

    if (root.contains("robots") && root["robots"].isArray()) {
        QJsonArray robotsArray = root["robots"].toArray();
        for (const auto& robotValue : robotsArray) {
            QJsonObject robotObj = robotValue.toObject();
            qreal x = robotObj["x"].toDouble();
            qreal y = robotObj["y"].toDouble();
            qreal angle = robotObj["angle"].toDouble();
            qreal speed = robotObj["speed"].toDouble();
            qreal turnAngle = robotObj["turnAngle"].toDouble();
            QString rotationDirection = robotObj["rotationDirection"].toString();
            QColor color(robotObj["color"].toString());
            qreal detectionDistance = robotObj["detectionDistance"].toDouble();

            Robot *robot = new Robot(angle, speed, turnAngle,
                                     rotationDirection == "Left" ? Robot::Left : Robot::Right,
                                     color, detectionDistance);
            robot->setPos(x, y);
            scene->addItem(robot);
        }
    }

    if (root.contains("userRobot") && root["userRobot"].isArray()) {
        QJsonArray robotsArray = root["userRobot"].toArray();
        for (const auto& robotValue : robotsArray) {
            QJsonObject robotObj = robotValue.toObject();
            qreal x = robotObj["x"].toDouble();
            qreal y = robotObj["y"].toDouble();
            //qreal angle = robotObj["angle"].toDouble();
            qreal speed = robotObj["speed"].toDouble();
            qreal size = robotObj["size"].toDouble();
            qreal turnAngle = robotObj["turnAngle"].toDouble();
            UserRobot *uRobot = new UserRobot(size, speed, turnAngle);
            uRobot->setPos(x, y);
            scene->addItem(uRobot);
            uRobot->setFocus();
        }
    }

    if (root.contains("obstacles") && root["obstacles"].isArray()) {
        QJsonArray obstaclesArray = root["obstacles"].toArray();
        for (const auto& obstacleValue : obstaclesArray) {
            QJsonObject obstacleObj = obstacleValue.toObject();
            qreal x = obstacleObj["x"].toDouble();
            qreal y = obstacleObj["y"].toDouble();

            Obstacle *obstacle = new Obstacle;
            obstacle->setPos(x, y);
            scene->addItem(obstacle);
        }
    }

    if (root.contains("scene") && root["scene"].isObject()) {
        QJsonObject sceneObj = root["scene"].toObject();
        int width = sceneObj["width"].toInt();
        int height = sceneObj["height"].toInt();
        scene->setSceneRect(0, 0, width, height);
        setScene(scene);
    }

}

// Slot to handle advancing the scene
void Simulation::advanceScene() {
    if (!isPaused) {
        scene->advance();
    }
}

// Slot to toggle pause/play
void Simulation::togglePause() {
    isPaused = !isPaused;
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        if (isPaused) {
            button->setText("Play");
        } else {
            button->setText("Pause");
        }
    }
}
