#include "tablist.h"

Tablist::Tablist(QWidget *parent)
    : QWidget{parent}
{
    layout = new QVBoxLayout(this);

    QPushButton* homeButton = new QPushButton("Home");
    layout->addWidget(homeButton);

    QPushButton* sensorButton = new QPushButton("My Sensors");
    layout->addWidget(sensorButton);
    // Popup with the current list of tables of sensors

    QPushButton* addButton = new QPushButton("Add Sensor");
    layout->addWidget(addButton);
    // Popup with list of all possible sensors to add

    QPushButton* settingsButton = new QPushButton("Settings");
    layout->addWidget(settingsButton);
}
