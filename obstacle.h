#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QWidget>
#include <QPointF>
#include <QPainter>

class Obstacle : public QWidget
{
    Q_OBJECT

private:
    QPointF position;

public:
    explicit Obstacle(double size, double x = 0, double y = 0, QWidget *parent = nullptr);
    QPointF getPosition() const;
    void setPosition(QPointF);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // OBSTACLE_H
