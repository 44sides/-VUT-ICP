#include "robot.h"
#include <QPainter>
#include <cmath>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include "obstacle.h"

Robot::Robot(qreal angle, qreal speed, qreal turnAngle, RotationDirection rotationDirection, QColor color, qreal detectionDistance)
    : angle(angle * M_PI / 180), speed(speed), turnAngle(turnAngle * M_PI / 180), rotationDirection(rotationDirection), color(color), detectionDistance(detectionDistance) {}

QRectF Robot::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color);
    painter->drawEllipse(-10, -10, 20, 20);

    painter->setPen(Qt::blue);
    painter->drawLine(0, 0, 10 * cos(angle), 10 * sin(angle));
}
void Robot::advance(int step) {
    if (!step)
        return;

    qreal dx = speed * cos(angle);
    qreal dy = speed * sin(angle);

    qreal robotRadius = 10; // Radius of the robot's circle

    // Calculate the position in front of the robot
    qreal frontX = x() + detectionDistance * cos(angle);
    qreal frontY = y() + detectionDistance * sin(angle);

    // Check boundaries
    if (frontX - robotRadius < 0 || frontX + robotRadius > scene()->width() || frontY - robotRadius < 0 || frontY + robotRadius > scene()->height()) {
        if (rotationDirection == Left)
            angle -= turnAngle;
        else
            angle += turnAngle;
    } else {
        // Check collision with obstacles
        bool obstacleCollision = false;
        QRectF robotBoundingRect = QRectF(frontX - robotRadius, frontY - robotRadius, 2 * robotRadius, 2 * robotRadius);

        QList<QGraphicsItem*> collidingItemsList = scene()->items(robotBoundingRect);
        for (auto item : collidingItemsList) {
            if (item != this && item->type() == Obstacle::Type) {
                Obstacle *obstacle = dynamic_cast<Obstacle*>(item);

                QPointF obstaclePos = item->pos(); // Obtain obstacle position
                qreal obstacleSize = obstacle->m_size; // Size of the obstacle, adjust as needed

                QRectF obstacleBoundingRect = QRectF(obstaclePos.x() - obstacleSize / 2, obstaclePos.y() - obstacleSize / 2, obstacleSize, obstacleSize);

                if (robotBoundingRect.intersects(obstacleBoundingRect)) {
                    obstacleCollision = true;
                    break;
                }
            }
        }
        if (obstacleCollision) {
            if (rotationDirection == Left)
                angle -= turnAngle;
            else
                angle += turnAngle;
        } else {
            setPos(mapToParent(dx, dy));
        }
    }
}

void Robot::rotate(qreal amount) {
    angle += amount;
}
