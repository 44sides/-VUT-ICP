#include "obstacle.h"

Obstacle::Obstacle(double size, double x, double y, QWidget *parent) :
    QWidget(parent),
    position(x, y)
{
    setFixedSize(size, size);
    setPosition(position);
}

QPointF Obstacle::getPosition() const
{
    return position;
}

void Obstacle::setPosition(QPointF point)
{
    move(point.toPoint());
}

void Obstacle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::red);
    painter.drawRect(rect());
}
