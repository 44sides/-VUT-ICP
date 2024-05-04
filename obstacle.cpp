#include "obstacle.h"
#include <QPainter>

Obstacle::Obstacle() {}

QRectF Obstacle::boundingRect() const {
    return QRectF(-20, -20, 40, 40);
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::red);
    painter->drawRect(-20, -20, 40, 40);
}
