#ifndef USERROBOT_H
#define USERROBOT_H

#include <QGraphicsItem>
#include <QKeyEvent>

class UserRobot : public QGraphicsItem
{
public:
    enum RotationDirection { None, Left, Right };

    UserRobot(qreal size = 20, qreal speed = 1, qreal turnAngle = 45);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void advance(int step) override;

    qreal size;
    qreal speed;
    qreal turnAngle;
    bool moving;
    RotationDirection rotating;
    qreal angle;
private:
    void updateMovement();

};

#endif // USERROBOT_H
