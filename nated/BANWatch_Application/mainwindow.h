#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QString>
#include <QTableView>
#include <QVector>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QTimer>

class Card;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    QVector<Card*> cardList;    // Vector of displayed widgets

    QVector<QString> tableList; // Vector of table names in database

    QTimer* updateTimer;        // Tells how frequently the sql query should be updated

    void testDatabase();        // Creates a database for testing purposes
    unsigned int time = 0;

private slots:
    void updateTestDatabase();
    void searchResults();
    void removeWidget();
    void updateTables();
};
#endif // MAINWINDOW_H
