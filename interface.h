// interface.h
#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QPushButton>
#include <QFileDialog>
#include "simulation.h"

class Interface : public QObject
{
    Q_OBJECT
public:
    explicit Interface(QWidget *parent = nullptr);

    void setSimulation(Simulation *simulation);

    void addPauseButton();
    void addJsonFileButton();
    void addExitButton();

signals:

private slots:
    void openJsonFile();
    void exitSimulation();

private:
    Simulation *m_simulation;

    QMenu *menu = nullptr;

    // QPoint m_pauseButtonPosition;
    // QPoint m_jsonFileButtonPosition;
    // QPoint m_exitButtonPosition;
    // QPushButton *pauseButton = nullptr;
    // QPushButton *jsonFileButton = nullptr;
    // QPushButton *exitButton = nullptr;
};

#endif // INTERFACE_H
