#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QTableView>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QString>
#include <QTableView>
#include <QVector>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>

class Card : public QWidget
{
    Q_OBJECT
public:
    explicit Card(QWidget *parent = nullptr);
    Card(QString, QSqlDatabase);
    ~Card();

    QTableView* table;  // Widget to display table
    QLabel* displayRecent;  // Widget to display most recent values

    QLabel* label;      // Widget to display Table's name
    QPushButton* changeType;    // Widget to change format of the card

    QString tableName;  // Name of the Table to use for Query

    QHBoxLayout* layout;
    QVBoxLayout* vlayout;

    unsigned short int widgetType;  // Tells what widget is being displayed
    const unsigned short int WIDGET_TYPES = 2;

    void updateWidget();

private:
    QSqlDatabase db;
    QSqlQueryModel* model;



signals:

private slots:
    void changeFormat();

};

#endif // CARD_H
