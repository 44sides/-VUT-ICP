#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsItem>

class Obstacle : public QGraphicsItem
{
public:
    enum { Type = UserType + 1 };

    Obstacle(int size = 40, int rotationAngle = 0); // Default size and rotation angle
    int type() const override { return Type; }
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    int m_size; // Size of the obstacle
    int m_rotationAngle; // Rotation angle of the obstacle
};

#endif // OBSTACLE_H
