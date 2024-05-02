#ifndef ROBOT_H
#define ROBOT_H

#include <QWidget>
#include <QPointF>
#include <QPainter>

class Robot : public QWidget
{
    Q_OBJECT
    private:
    QPointF position;
    public:
        explicit Robot(double x = 0, double y = 0, QWidget *parent = nullptr);

        QPointF getPosition() const;
        void setPosition(double x, double y);

    protected:
        void paintEvent(QPaintEvent *event) override;
};

#endif // ROBOT_H
