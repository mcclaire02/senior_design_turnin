#ifndef TABLIST_H
#define TABLIST_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>

class Tablist : public QWidget
{
    Q_OBJECT
public:
    explicit Tablist(QWidget *parent = nullptr);

private:
    QVBoxLayout* layout;

    void addSensor();

signals:

};

#endif // TABLIST_H
