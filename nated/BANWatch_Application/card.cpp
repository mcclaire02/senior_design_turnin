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



    QString s = "SELECT * FROM " + tableName;
    model->setQuery(s, db);

    table->setModel(model);
    model->setHeaderData(0, Qt::Horizontal, "Sensor");
    model->setHeaderData(1, Qt::Horizontal, "Value1");
    model->setHeaderData(2, Qt::Horizontal, "Value2");

    changeType = new QPushButton("Change Format");
    connect(changeType, &QPushButton::clicked, this, &Card::changeFormat);

    vlayout->addWidget(label);
    vlayout->addWidget(table);
    vlayout->addWidget(changeType);

    layout->addLayout(vlayout);


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
    switch(widgetType)
    {
        // Display the Table
        case 0:

        break;
        // Display the most recent value
        case 1:

        break;
    }
}

