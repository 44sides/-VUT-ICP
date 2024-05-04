#include "robot.h"
#include <QPainter>
#include <cmath>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include "obstacle.h" // Include Obstacle header

Robot::Robot(qreal angle, qreal speed, qreal turnAngle, RotationDirection rotationDirection, QColor color, qreal detectionDistance)
    : angle(angle * M_PI / 180), speed(speed), turnAngle(turnAngle * M_PI / 180), rotationDirection(rotationDirection), color(color), detectionDistance(detectionDistance) {}

QRectF Robot::boundingRect() const {
    return QRectF(-10, -10, 20, 20);
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(color);
    painter->drawEllipse(-10, -10, 20, 20);

    // Draw movement direction line
    painter->setPen(Qt::blue);
    painter->drawLine(0, 0, 20 * cos(angle), 20 * sin(angle));
}

void Robot::advance(int step) {
    if (!step)
        return;

    qreal dx = speed * cos(angle);
    qreal dy = speed * sin(angle);
    qreal newX = x() + dx;
    qreal newY = y() + dy;

    // Check boundaries
    if (newX < 0 || newX > scene()->width() || newY < 0 || newY > scene()->height()) {
        if (rotationDirection == Left)
            angle += turnAngle;
        else
            angle -= turnAngle;
    } else {
        setPos(mapToParent(dx, dy));
    }

    // Check collision with obstacles
    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    for (auto item : collidingItemsList) {
        if (item->type() == Obstacle::Type) {
            if (rotationDirection == Left)
                angle += turnAngle;
            else
                angle -= turnAngle;
            break;
        }
    }
}

void Robot::rotate(qreal amount) {
    angle += amount * M_PI / 180;
}
