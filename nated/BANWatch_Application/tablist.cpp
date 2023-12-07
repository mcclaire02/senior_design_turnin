#include "tablist.h"

Tablist::Tablist(QWidget *parent)
    : QWidget{parent}
{
    layout = new QVBoxLayout(this);

    QPushButton* homeButton = new QPushButton("Home");
    layout->addWidget(homeButton);

    QPushButton* sensorButton = new QPushButton("Sensors");
    layout->addWidget(sensorButton);

    QPushButton* addButton = new QPushButton("Add Sensor");
    layout->addWidget(addButton);

    QPushButton* settingsButton = new QPushButton("Settings");
    layout->addWidget(settingsButton);
}
