#include "userRobot.h"
#include "obstacle.h" // Include Obstacle header
#include <QPainter>
#include <cmath>
#include <QGraphicsScene> // Include QGraphicsScene header

UserRobot::UserRobot(qreal size, qreal speed, qreal turnAngle)
    : size(size), speed(speed), turnAngle(turnAngle), moving(false), rotating(None), angle(0) {
    setFlags(ItemIsFocusable);
}

QRectF UserRobot::boundingRect() const {
    return QRectF(-size / 2, -size / 2, size, size);
}

void UserRobot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::red);
    painter->drawEllipse(boundingRect());

    // Draw movement direction line
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
    if (event->key() == Qt::Key_W) {
        // Do nothing on key release to keep moving after 'W' is released
    } else if ((event->key() == Qt::Key_A || event->key() == Qt::Key_D) && rotating != None) {
        rotating = None;
    }
}

void UserRobot::advance(int step) {
    if (step == 0) return;

    if (moving) {
        qreal dx = speed * cos(angle);
        qreal dy = speed * sin(angle);
        qreal newX = x() + dx;
        qreal newY = y() + dy;

        // Check boundaries
        if (newX < 0 || newX > scene()->width() || newY < 0 || newY > scene()->height()) {
            moving = false;
        }

        // Check collision with obstacles
        QList<QGraphicsItem*> collidingItemsList = collidingItems();
        for (auto item : collidingItemsList) {
            if (item->type() == Obstacle::Type) {
                moving = false;
            }
        }

        setPos(mapToParent(dx, dy));
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
