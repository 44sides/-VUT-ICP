#include "robot.h"

Robot::Robot(double x, double y, QWidget *parent) :
    QWidget(parent),
    position(x, y)
{
    // Set default size for the widget
    setFixedSize(20, 20);
}

QPointF Robot::getPosition() const
{
    return position;
}

void Robot::setPosition(double x, double y)
{
    position.setX(x);
    position.setY(y);
    update(); // Trigger repaint
}

void Robot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(rect());
}
