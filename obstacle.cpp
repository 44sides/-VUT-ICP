#include "obstacle.h"
#include <QPainter>

Obstacle::Obstacle(int size, int rotationAngle) : m_size(size), m_rotationAngle(rotationAngle) {}

QRectF Obstacle::boundingRect() const {
    return QRectF(-m_size / 2, -m_size / 2, m_size, m_size);
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    // Translate to the center of the bounding rectangle
    painter->translate(0, 0);

    // Rotate the painter by the specified angle
    painter->rotate(m_rotationAngle);

    // Draw the obstacle
    painter->setBrush(Qt::red);
    painter->drawRect(-m_size / 2, -m_size / 2, m_size, m_size);
}
