/*!
 * @file obstacle.cpp
 * @author Josef Susík (xsusik00)
 * @author Vladyslav Tverdokhlib (xtverd01)
 * @brief Obstacle implementation
 */

#include "obstacle.h"
#include <QPainter>

/**
 * @brief Constructs an Obstacle object.
 * @param size The size of the obstacle.
 * @param rotationAngle The rotation angle of the obstacle.
 */
Obstacle::Obstacle(int size, int rotationAngle) : m_size(size), m_rotationAngle(rotationAngle) {}

/**
 * @brief Returns the bounding rectangle of the obstacle.
 * @return The bounding rectangle of the obstacle.
 */
QRectF Obstacle::boundingRect() const {
    return QRectF(-m_size / 2, -m_size / 2, m_size, m_size);
}

/**
 * @brief Paints the obstacle on the scene.
 * @param painter The painter object used for painting.
 * @param option Not used.
 * @param widget Not used.
 */
void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    // Translate to the center of the bounding rectangle
    painter->translate(0, 0);

    // Rotate the painter by the specified angle
    painter->rotate(m_rotationAngle);

    // Draw the obstacle
    painter->setBrush(Qt::red);
    painter->drawRect(-m_size / 2, -m_size / 2, m_size, m_size);
}
