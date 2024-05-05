/*!
 * @file robot.cpp
 * @author Josef Susík (xsusik00)
 * @author Vladyslav Tverdokhlib (xtverd01)
 * @brief Autonomous robot implementation
 */


#include "robot.h"
#include <QPainter>
#include <cmath>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include "obstacle.h"

/**
 * @brief Constructs a Robot object.
 * @param angle The initial angle of the robot.
 * @param speed The speed of the robot.
 * @param turnAngle The turning angle of the robot.
 * @param rotationDirection The rotation direction of the robot.
 * @param color The color of the robot.
 * @param detectionDistance The detection distance of the robot.
 */
Robot::Robot(qreal angle, qreal speed, qreal turnAngle, RotationDirection rotationDirection, QColor color, qreal detectionDistance)
    : angle(angle * M_PI / 180), speed(speed), turnAngle(turnAngle * M_PI / 180), rotationDirection(rotationDirection), color(color), detectionDistance(detectionDistance) {}

/**
 * @brief Returns the bounding rectangle of the robot.
 * @return The bounding rectangle of the robot.
 */
QRectF Robot::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

/**
 * @brief Paints the robot on the scene.
 * @param painter The painter object used for painting.
 * @param option Not used.
 * @param widget Not used.
 */
void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color);
    painter->drawEllipse(-10, -10, 20, 20);

    painter->setPen(Qt::blue);
    painter->drawLine(0, 0, 10 * cos(angle), 10 * sin(angle));
}

/**
 * @brief Advances the robot's movement and collision detection.
 * @param step Not used.
 */
void Robot::advance(int step) {
    if (!step)
        return;

    qreal dx = speed * cos(angle);
    qreal dy = speed * sin(angle);

    qreal robotRadius = 10; // Radius of the robot's circle

    qreal frontX = x() + 1 * cos(angle);
    qreal frontY = y() + 1 * sin(angle);
    // Calculate the position in front of the robot
    if(detectionDistance > 0) {
        frontX = x() + detectionDistance * cos(angle);
        frontY = y() + detectionDistance * sin(angle);
    }

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

/**
 * @brief Rotates the robot by the specified amount.
 * @param amount The amount by which to rotate the robot.
 */
void Robot::rotate(qreal amount) {
    angle += amount;
}
