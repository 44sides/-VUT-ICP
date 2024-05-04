#include "robot.h"

Robot::Robot(double radius, double x, double y, QWidget *parent) :
    QWidget(parent),
    position(x, y)
{
    setFixedSize(radius * 2, radius * 2);
    setPosition(position);
}

QPointF Robot::getPosition() const
{
    return position;
}

void Robot::setPosition(QPointF point)
{
    move(point.toPoint());
}

void Robot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(rect());
}
