// Card.cpp
// Makes a card that queries a specific table from the database
// Can be displayed in different formats
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
    displayRecent = new QLabel();
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
    // todo: clean up code to only use show/hide instead of add
    // Update the Query
    QString s = "SELECT * FROM " + tableName;
    model->setQuery(s, db);

    switch(widgetType)
    {
    // Display the Table
    case 0:
    {
        displayRecent->hide();

        table->setModel(model);
        model->setHeaderData(0, Qt::Horizontal, "Sensor");
        model->setHeaderData(1, Qt::Horizontal, "Value1");
        model->setHeaderData(2, Qt::Horizontal, "Value2");
        vlayout->addWidget(label);
        vlayout->addWidget(table);
        vlayout->addWidget(changeType);

        table->show();
        break;
    }
    // Display the most recent value
    case 1:
    {
        table->hide();

        // Loop to find what the most recent value is
        QSqlQuery qprep;
        QString data;
        qprep.exec("SELECT * FROM " + tableName);
        while(qprep.next())
        {
            // Get the most recent set of data
            data = "Time: " + qprep.value(0).toString() + "| Value: " + qprep.value(1).toString();
        }
        displayRecent->setText(data);
        vlayout->addWidget(label);
        vlayout->addWidget(displayRecent);
        vlayout->addWidget(changeType);

        displayRecent->show();
        break;
    }
    }

}

