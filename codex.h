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
#include <QSignalMapper>
#include <utility>

class Controller;

class Codex : public QDialog
{
    Q_OBJECT
private:
    Controller* c;
    QScrollArea* container;
    QTextEdit* details;

public:
    explicit Codex(QWidget *parent = nullptr);

    void addScrollArea();

signals:

public slots:
    void showDetails(int i);

};

#endif // CODEX_H
