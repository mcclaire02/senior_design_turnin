#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "card.h"
#include "tablist.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchResults);

    // Restrict input to prevent SQL injections
    QRegularExpression* regex = new QRegularExpression("[A-Za-z0-9]{12}");
    QRegularExpressionValidator* v = new QRegularExpressionValidator(*regex);
    ui->lineEdit->setValidator(v);

    Tablist* tablist = new Tablist();
    ui->verticalLayout->addWidget(tablist);

    //db = QSqlDatabase::addDatabase("MYSQL");
    // need the access info
    // db.setHostName();
    // db.setDatabaseName();
    // db.setUserName("user");
    // db.setPassword("User123!");
    // db.open();

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");

    if (!db.open())
    {
        qDebug() << "Error Opening Database: " << db.lastError();
        exit(1);
    }

    testDatabase();
    // figure out how to query multiple tables

    // somekind of display all method
    // grabs all tables and creates Cards for them

    // What needs to be done:
    // Create the cards and put them on the MainWindow
    // Query and display the values onto the Cards
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::searchResults()
{
    QString input = ui->lineEdit->text();
    ui->lineEdit->clear();
    // Looking at the search Result, create a query on the tables
    // Table names that match the search are added to the
    // cardList and query is done handled on the Card

    // Empty cardList
    for(int i = 0; i < cardList.size(); i++)
    {
        // Delete all elements in cardList
        ui->formLayout->removeItem(cardList[i]->layout);
        cardList[i]->deleteLater();
    }
    cardList.clear();


    Card* card = new Card(input, db);
    cardList.push_back(card);

    ui->formLayout->addWidget(card);


    // somekind of loop that creates new Card based on sql

    // need to set this up in card

    // group exit connect when lineEdit is changed again

}

void MainWindow::removeWidget()
{
    QTableView* table = qobject_cast<QTableView*>(sender());
    delete table;
}

void MainWindow::testDatabase()
{
    QSqlQuery qprep;

    if (qprep.exec("DROP TABLE IF EXISTS test"))
    {
        qDebug() << "Dropped existing test table.";
    }
    qprep.exec("CREATE TABLE IF NOT EXISTS test (Sensor TEXT, Value1 INTEGER, Value2 INTEGER )");
    qprep.exec("INSERT INTO test VALUES('Accelerometer', 600, 800);");

    if (qprep.exec("DROP TABLE IF EXISTS test2"))
    {
        qDebug() << "Dropped existing test2 table.";
    }
    qprep.exec("CREATE TABLE IF NOT EXISTS test2 (Sensor TEXT, Value1 INTEGER, Value2 INTEGER )");
    qprep.exec("INSERT INTO test2 VALUES('Accelerometer', 600, 800);");
}

void MainWindow::updateTables()
{
    // update tables
}
