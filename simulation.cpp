#include "simulation.h"
#include <QPushButton>
#include <QGraphicsRectItem>

Simulation::Simulation(QObject *parent, QString path) : QGraphicsScene(parent)
{
    loadFromJson(path);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Simulation::advanceScene);

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
            this->addItem(robot);
        }
    }

    if (root.contains("userRobot") && root["userRobot"].isArray()) {
        QJsonArray robotsArray = root["userRobot"].toArray();
        for (const auto& robotValue : robotsArray) {
            QJsonObject robotObj = robotValue.toObject();
            qreal x = robotObj["x"].toDouble();
            qreal y = robotObj["y"].toDouble();
            qreal speed = robotObj["speed"].toDouble();
            qreal size = robotObj["size"].toDouble();
            qreal turnAngle = robotObj["turnAngle"].toDouble();
            UserRobot *uRobot = new UserRobot(size, speed, turnAngle);
            uRobot->setPos(x, y);
            this->addItem(uRobot);
            uRobot->setFocus();
        }
    }

    if (root.contains("obstacles") && root["obstacles"].isArray()) {
        QJsonArray obstaclesArray = root["obstacles"].toArray();
        for (const auto& obstacleValue : obstaclesArray) {
            QJsonObject obstacleObj = obstacleValue.toObject();
            qreal x = obstacleObj["x"].toDouble();
            qreal y = obstacleObj["y"].toDouble();
            qreal rotation = obstacleObj["rotation"].toDouble();
            qreal size = obstacleObj["size"].toDouble();

            Obstacle *obstacle = new Obstacle(size, rotation);
            obstacle->setPos(x, y);
            this->addItem(obstacle);
        }
    }

    if (root.contains("scene") && root["scene"].isObject()) {
        QJsonObject sceneObj = root["scene"].toObject();
        int width = sceneObj["width"].toInt();
        int height = sceneObj["height"].toInt();
        this->setSceneRect(0, 0, width, height);
        //setScene(this);
        QGraphicsRectItem *border = new QGraphicsRectItem(0, 0, width, height);
        border->setPen(QPen(Qt::blue, 2));
        border->setBrush(Qt::NoBrush);
        this->addItem(border);
    }

}

void Simulation::advanceScene() {
    if (!isPaused) {
        this->advance();
    }
}

void Simulation::togglePause() {
    isPaused = !isPaused;
}

void Simulation::addRobot(qreal x, qreal y, qreal angle, qreal speed, qreal turnAngle, const QString& rotationDirection, const QColor& color, qreal detectionDistance) {
    Robot *robot = new Robot(angle, speed, turnAngle,
                             rotationDirection == "Left" ? Robot::Left : Robot::Right,
                             color, detectionDistance);
    robot->setPos(x, y);
    this->addItem(robot);
}

void Simulation::addObstacle(qreal x, qreal y, qreal size, qreal rotation) {
    Obstacle *obstacle = new Obstacle(size, rotation);
    obstacle->setPos(x, y);
    this->addItem(obstacle);
}


void Simulation::saveToJson(const QString& filename) {
    QJsonObject root;

    // Add scene dimensions
    QJsonObject sceneObj;
    sceneObj["width"] = static_cast<int>(this->width());
    sceneObj["height"] = static_cast<int>(this->height());
    root["scene"] = sceneObj;

    // Add userRobot objects
    QJsonArray userRobotArray;
    QList<QGraphicsItem *> userRobots = this->items();
    for (QGraphicsItem *item : userRobots) {
        if (UserRobot *uRobot = dynamic_cast<UserRobot *>(item)) {
            QJsonObject userRobotObj;
            userRobotObj["x"] = static_cast<int>(uRobot->x());
            userRobotObj["y"] = static_cast<int>(uRobot->y());
            userRobotObj["size"] = static_cast<int>(uRobot->size);
            userRobotObj["angle"] = static_cast<int>(uRobot->angle);
            userRobotObj["speed"] = static_cast<double>(uRobot->speed);
            userRobotObj["turnAngle"] = static_cast<int>(uRobot->turnAngle);
            userRobotArray.append(userRobotObj);
        }
    }
    root["userRobot"] = userRobotArray;

    // Add robot objects
    QJsonArray robotsArray;
    QList<QGraphicsItem *> robots = this->items();
    for (QGraphicsItem *item : robots) {
        if (Robot *robot = dynamic_cast<Robot *>(item)) {
            QJsonObject robotObj;
            robotObj["x"] = static_cast<int>(robot->x());
            robotObj["y"] = static_cast<int>(robot->y());
            robotObj["angle"] = static_cast<int>(robot->angle);
            robotObj["speed"] = robot->speed;
            robotObj["turnAngle"] = robot->turnAngle;
            robotObj["rotationDirection"] = robot->rotationDirection == Robot::Left ? "Left" : "Right";
            robotObj["color"] = robot->color.name(QColor::HexRgb);
            robotObj["detectionDistance"] = robot->detectionDistance;
            robotsArray.append(robotObj);
        }
    }
    root["robots"] = robotsArray;

    // Add obstacle objects
    QJsonArray obstaclesArray;
    QList<QGraphicsItem *> obstacles = this->items();
    for (QGraphicsItem *item : obstacles) {
        if (Obstacle *obstacle = dynamic_cast<Obstacle *>(item)) {
            QJsonObject obstacleObj;
            obstacleObj["x"] = static_cast<int>(obstacle->x());
            obstacleObj["y"] = static_cast<int>(obstacle->y());
            obstacleObj["size"] = static_cast<int>(obstacle->m_size);
            obstacleObj["rotation"] = static_cast<int>(obstacle->m_rotationAngle);

            obstaclesArray.append(obstacleObj);
        }
    }
    root["obstacles"] = obstaclesArray;

    // Write JSON to file
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open JSON file for writing.");
        return;
    }
    QJsonDocument doc(root);
    file.write(doc.toJson());
    file.close();
}

