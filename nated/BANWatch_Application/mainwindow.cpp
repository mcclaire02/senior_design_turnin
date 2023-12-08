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
    QRegularExpression* regex = new QRegularExpression("[A-Za-z0-9]{20}");
    QRegularExpressionValidator* v = new QRegularExpressionValidator(*regex);
    ui->lineEdit->setValidator(v);

    // Timer to update the Query
    QTimer* timer = new QTimer;
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTables);
    timer->start();

    // List of tabs on the right of the screen
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
    // Setup Database for testing
    testDatabase();

    QSqlQuery qprep;
    qprep.exec("DROP TABLE IF EXISTS tables");
    qprep.exec("CREATE TABLE IF NOT EXISTS tables (Sensor TEXT)");
    qprep.exec("INSERT INTO tables VALUES('temperature');");
    qprep.exec("INSERT INTO tables VALUES('accelerometer');");
    qprep.exec("SELECT * FROM tables");
    while(qprep.next())
    {
        tableList.push_back(qprep.value(0).toString());
    }
    qDebug() << tableList;
    showAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::searchResults()
{
    QString input = ui->lineEdit->text();
    ui->lineEdit->clear();

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
}

// Testing code that creates database
void MainWindow::testDatabase()
{
    QSqlQuery qprep;

    if (qprep.exec("DROP TABLE IF EXISTS temperature"))
    {
        qDebug() << "Dropped existing temperature table.";
    }
    qprep.exec("CREATE TABLE IF NOT EXISTS temperature (time INTEGER, temp INTEGER)");

    if (qprep.exec("DROP TABLE IF EXISTS accelerometer"))
    {
        qDebug() << "Dropped existing accelerometer table.";
    }
    qprep.exec("CREATE TABLE IF NOT EXISTS accelerometer (time INTEGER, x INTEGER)");

    QTimer* timer = new QTimer();
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTestDatabase);
    timer->start();
    QString s = "INSERT INTO temperature VALUES(0, 72);";
    qprep.exec(s);
}

// Testing code that inserts value to database
void MainWindow::updateTestDatabase()
{
    time += 500;
    QSqlQuery qprep;
    QString s = "INSERT INTO temperature VALUES(" + QString::number(time) + ", 72);";
    QString x = "INSERT INTO accelerometer VALUES(" + QString::number(time) + ", 23);";
    qprep.exec(s);
    qprep.exec(x);
}

// Updates the Query on Cards
void MainWindow::updateTables()
{
    // update tables
    for(int i = 0; i < cardList.size(); i++)
    {
        cardList[i]->updateWidget();
    }
}

void MainWindow::showAll()
{
    // Show all
    for(int i = 0; i < tableList.size(); i++)
    {
        Card* card = new Card(tableList[i], db);
        ui->formLayout->addWidget(card);
        cardList.push_back(card);
    }
    updateTables();
}
