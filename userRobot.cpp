#include "userRobot.h"
#include "obstacle.h"
#include <QPainter>
#include <cmath>
#include <QGraphicsScene>

UserRobot::UserRobot(qreal size, qreal speed, qreal turnAngle)
    : size(size), speed(speed), turnAngle(turnAngle), moving(false), rotating(None), angle(0) {
    setFlags(ItemIsFocusable);
}

QRectF UserRobot::boundingRect() const {
    return QRectF(-size / 2, -size / 2, size, size);
}

void UserRobot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    QColor neonPink(255, 105, 180); // RGB values for neon pink
    painter->setBrush(neonPink);
    painter->drawEllipse(boundingRect());

    painter->setPen(Qt::blue);
    painter->drawLine(0, 0, size / 2 * cos(angle), size / 2 * sin(angle));
}

void UserRobot::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W:
        moving = true;
        if (!moving) {
            moving = true;
            updateMovement();
        }
        break;
    case Qt::Key_S:
        moving = false;
        break;
    case Qt::Key_A:
        rotating = Left;
        break;
    case Qt::Key_D:
        rotating = Right;
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
        return;
    }
}

void UserRobot::keyReleaseEvent(QKeyEvent *event) {
    if ((event->key() == Qt::Key_A || event->key() == Qt::Key_D) && rotating != None) {
        rotating = None;
    }
}

void UserRobot::advance(int step) {
    if (!step)
        return;

    if (moving) {
        qreal dx = speed * cos(angle);
        qreal dy = speed * sin(angle);
        qreal newX = x() + dx;
        qreal newY = y() + dy;

        qreal robotRadius = size/2; // Radius of the robot's circle, adjust as needed

        // Check boundaries
        if (newX - robotRadius < 0 || newX + robotRadius > scene()->width() || newY - robotRadius < 0 || newY + robotRadius > scene()->height()) {
            moving = false;
        } else {
            // Check collision with obstacles
            bool obstacleCollision = false;
            QRectF robotBoundingRect = QRectF(newX - robotRadius, newY - robotRadius, 2 * robotRadius, 2 * robotRadius);
            QList<QGraphicsItem*> collidingItemsList = scene()->items(robotBoundingRect);
            for (auto item : collidingItemsList) {
                if (item != this && item->type() == Obstacle::Type) {
                    QPointF obstaclePos = item->pos(); // Obtain obstacle position
                    qreal obstacleSize = 40; // Size of the obstacle, adjust as needed
                    QRectF obstacleBoundingRect = QRectF(obstaclePos.x() - obstacleSize / 2, obstaclePos.y() - obstacleSize / 2, obstacleSize, obstacleSize);
                    qDebug() << "Robot: " << robotBoundingRect;
                    qDebug() << "Obs: " << obstacleBoundingRect;
                    if (robotBoundingRect.intersects(obstacleBoundingRect)) {
                        obstacleCollision = true;
                        break;
                    }
                }
            }
            if (obstacleCollision) {
                moving = false;
            } else {
                setPos(mapToParent(dx, dy));
            }
        }
    }
    if (rotating != None) {
        qreal rotationAmount = rotating == Left ? -turnAngle : turnAngle;
        angle += rotationAmount * M_PI / 180;
        update();
    }
}
void UserRobot::updateMovement() {
    if (moving) {
        qreal dx = speed * cos(angle);
        qreal dy = speed * sin(angle);
        qreal newX = x() + dx;
        qreal newY = y() + dy;

        // Check boundaries
        if (newX < 0 || newX > scene()->width() || newY < 0 || newY > scene()->height()) {
            return;
        }

        // Check collision with obstacles
        QList<QGraphicsItem*> collidingItemsList = collidingItems();
        for (auto item : collidingItemsList) {
            if (item->type() == Obstacle::Type) {
                return;
            }
        }

        setPos(mapToParent(dx, dy));
    }

    if (rotating != None) {
        qreal rotationAmount = rotating == Left ? -turnAngle : turnAngle;
        angle += rotationAmount * M_PI / 180;
    }
}
