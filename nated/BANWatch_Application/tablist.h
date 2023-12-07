#ifndef TABLIST_H
#define TABLIST_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>

class Tablist : public QWidget
{
    Q_OBJECT
public:
    explicit Tablist(QWidget *parent = nullptr);

private:
    QVBoxLayout* layout;

signals:

};

#endif // TABLIST_H
