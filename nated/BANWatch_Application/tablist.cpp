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
    connect(addButton, &QPushButton::clicked, this, &Tablist::addSensor);
    // Popup with list of all possible sensors to add

    QPushButton* settingsButton = new QPushButton("Settings");
    layout->addWidget(settingsButton);
}

void Tablist::addSensor()
{
    // Have line edit that lets you enter sensor
    QDialog d;
    QVBoxLayout layout(&d);
    //QLabel label1("Help");
    //layout.addWidget(&label1);
    d.exec();
}
