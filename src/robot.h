/*!
 * @file robot.h
 * @author Josef Susík (xsusik00)
 * @author Vladyslav Tverdokhlib (xtverd01)
 * @brief Autonomous robot header
 */


#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItem>
#include <QKeyEvent>

class Robot : public QGraphicsItem
{
public:
    enum RotationDirection { Left, Right };

    Robot(qreal angle = 0, qreal speed = 1, qreal turnAngle = 45, RotationDirection rotationDirection = Left, QColor color = Qt::green, qreal detectionDistance = 10);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int step) override;
    void rotate(qreal amount);

    qreal angle;
    qreal speed;
    qreal turnAngle;
    RotationDirection rotationDirection;
    QColor color;
    qreal detectionDistance;
};

#endif // ROBOT_H
