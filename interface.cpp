#include "interface.h"
#include <QMenuBar>

#include <QDebug>

Interface::Interface(QWidget *parent) : QObject(parent), m_simulation(nullptr)
{
    // m_pauseButtonPosition = QPoint(100, 110);
    // m_jsonFileButtonPosition = QPoint(100, 160);
    // m_exitButtonPosition = QPoint(100, 210);

    QMenuBar *menuBar = new QMenuBar(qobject_cast<QWidget*>(parent));
    menu = menuBar->addMenu("Actions");

    menuBar->setStyleSheet("QMenuBar { border: none; font-weight: bold; }"
                           "QMenu::item { background-color: transparent; font-size: 15pt; font-weight: bold; }"
                           "QMenu::item:selected { background-color: #666; }"
                           "QMenu::item:pressed { background-color: #444; }");
}

void Interface::setSimulation(Simulation *simulation)
{
    m_simulation = simulation;

    QAction *pauseAction = menu->addAction("Play/Pause");
    connect(pauseAction, &QAction::triggered, m_simulation, &Simulation::togglePause);

    QAction *jsonAction = menu->addAction("Load JSON");
    connect(jsonAction, &QAction::triggered, this, &Interface::openJsonFile);

    QAction *exitAction = menu->addAction("Exit");
    connect(exitAction, &QAction::triggered, this, &Interface::exitSimulation);
}

// void Interface::addPauseButton()
// {
//     pauseButton = new QPushButton("Play", qobject_cast<QWidget*>(m_simulation));
//     pauseButton->move(m_pauseButtonPosition);
//     connect(pauseButton, &QPushButton::clicked, m_simulation, &Simulation::togglePause);
// }

// void Interface::addJsonFileButton()
// {
//     jsonFileButton = new QPushButton("JSON", qobject_cast<QWidget*>(m_simulation));
//     jsonFileButton->move(m_jsonFileButtonPosition);
//     connect(jsonFileButton, &QPushButton::clicked, this, &Interface::openJsonFile);
// }

// void Interface::addExitButton()
// {
//     exitButton = new QPushButton("Exit", qobject_cast<QWidget*>(m_simulation));
//     exitButton->move(m_exitButtonPosition);
//     connect(exitButton, &QPushButton::clicked, this, &Interface::exitSimulation);
// }

void Interface::openJsonFile()
{
    QString fileName = QFileDialog::getOpenFileName(qobject_cast<QWidget*>(m_simulation), "Open JSON File", QString(), "JSON Files (*.json)");
    if (!fileName.isEmpty()) {
        m_simulation->clearUserRobots();
        m_simulation->clearSceneBorders();

        m_simulation->loadFromJson(fileName);
    }
}

void Interface::exitSimulation()
{
    if (m_simulation) {
        m_simulation->close();
    }
}

