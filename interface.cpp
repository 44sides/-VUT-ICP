#include "interface.h"

Interface::Interface(QWidget *parent) : QObject(parent), m_simulation(nullptr)
{
    QPushButton *pauseButton = new QPushButton("Pause", qobject_cast<QWidget*>(parent));
    setSimulation(qobject_cast<Simulation*>(parent));
    setupButton(pauseButton);
}

void Interface::setSimulation(Simulation *simulation)
{
    m_simulation = simulation;
}

void Interface::setupButton(QPushButton *pauseButton)
{
    m_pauseButton = pauseButton;
    connect(m_pauseButton, &QPushButton::clicked, m_simulation, &Simulation::togglePause);
}
