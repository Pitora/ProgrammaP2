#ifndef CODEX_H
#define CODEX_H

#include "controller/controller.h"
#include "window.h"

#include <QWidget>
#include <QPushButton>
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
    Controller* controller;
    QListWidget* cont;
    QTextEdit* details;
    QPushButton* remove_item;
    QPushButton* import_item;
    QPushButton* export_item;

public:
    explicit Codex(Controller* cont, QList<QString> list, QWidget *parent = nullptr);

    void addScrollArea(QList<QString> l);
    void addControls();

    void refreshCodex(QList<QString> l);

    QString getSelectedItem();

    QString showExpDialog();
    QString showImportDialog();

signals:

public slots:
    void showDetails(QString s);

};

#endif // CODEX_H
