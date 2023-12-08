// tablist.cpp
// Creates a list of buttons to leftside of mainwindow
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
    QDialog* d = new QDialog();
    QVBoxLayout layout(d);
    QHBoxLayout hlayout;

    QPushButton* submitButton = new QPushButton("Submit");
    connect(submitButton, &QPushButton::clicked, d, &QDialog::accept);

    QLineEdit lineEdit;
    hlayout.addWidget(&lineEdit);
    // todo: Need to add filter
    hlayout.addWidget(submitButton);
    // todo: need to add connection from lineedit to push to tablelist

    QLabel label1("Enter in sensor");

    layout.addWidget(&label1);
    layout.addLayout(&hlayout);
    d->exec();
}
