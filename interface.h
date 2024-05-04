// interface.h
#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QPushButton>
#include "simulation.h"

class Interface : public QObject
{
    Q_OBJECT
public:
    explicit Interface(QWidget *parent = nullptr);

    void setupButton(QPushButton *pauseButton);
    void setSimulation(Simulation *simulation);

signals:

public slots:

private:
    QPushButton *m_pauseButton;
    Simulation *m_simulation;
};

#endif // INTERFACE_H
