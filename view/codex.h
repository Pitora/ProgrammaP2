#ifndef CODEX_H
#define CODEX_H

#include "controller/controller.h"
#include "window.h"

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QList>
#include <QListWidget>
#include "smartcombobox.h"
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
    SmartComboBox* sort_item;

public:
    explicit Codex(Controller* cont, QList<QString> list, QList<int> id, QWidget *parent = nullptr);

    void addScrollArea(QList<QString> l, QList<int> id);
    void addControls(QVBoxLayout *layout);

    void refreshCodex(QList<QString> l, QList<int> id);

    QListWidgetItem *getSelectedItem();
    int getSortInd();

    QString showExpDialog();
    QString showImportDialog();

signals:

public slots:
    void showDetails(QString s);

};

#endif // CODEX_H
