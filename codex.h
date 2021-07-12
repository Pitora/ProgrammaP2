#ifndef CODEX_H
#define CODEX_H

#include "controller.h"
#include "window.h"

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QList>
#include <QListWidget>
#include <QSignalMapper>
#include <utility>

class Controller;

class Codex : public QDialog
{
    Q_OBJECT
private:
    Controller* c;
    QScrollArea* container;
    QListWidget* cont;
    QTextEdit* details;
    QPushButton* remove_item;
    QPushButton* import_item;
    QPushButton* export_item;

public:
    explicit Codex(Controller* cont,QWidget *parent = nullptr);

    void addScrollArea();
    void addControls();

signals:

public slots:
    void showDetails(QString s);

};

#endif // CODEX_H
