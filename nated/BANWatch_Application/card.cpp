#include "card.h"

Card::Card(QWidget *parent)
    : QWidget{parent}{}

Card::Card(QString name, QSqlDatabase database)
{
    layout = new QHBoxLayout(this);
    vlayout = new QVBoxLayout();
    widgetType = 0;

    model = new QSqlQueryModel(this);
    table = new QTableView();
    tableName = name;
    label = new QLabel();
    label->setText("Table: " + tableName);
    db = database;

    // Button that changes the format of the Card
    changeType = new QPushButton("Change Format");
    connect(changeType, &QPushButton::clicked, this, &Card::changeFormat);

    layout->addLayout(vlayout);
    updateWidget();
}

Card::~Card()
{

}

void Card::changeFormat()
{
    widgetType++;
    if(widgetType == WIDGET_TYPES)
    {
        widgetType = 0;
    }
    updateWidget();
}

void Card::updateWidget()
{
    // Update the Query
    QString s = "SELECT * FROM " + tableName;
    model->setQuery(s, db);

    switch(widgetType)
    {
    // Display the Table
    case 0:
    {
        table->setModel(model);
        model->setHeaderData(0, Qt::Horizontal, "Sensor");
        model->setHeaderData(1, Qt::Horizontal, "Value1");
        model->setHeaderData(2, Qt::Horizontal, "Value2");
        vlayout->addWidget(label);
        vlayout->addWidget(table);
        vlayout->addWidget(changeType);
        break;
    }
    // Display the most recent value
    case 1:
    {
        // Loop to find what the most recent value is
        break;
    }
    }

}

