#ifndef CODEX_H
#define CODEX_H

#include "controller.h"
#include "window.h"

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QTabWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpacerItem>
#include <utility>

class Controller;

class Codex : public QWidget
{
    Q_OBJECT
private:
    Controller* c;

public:
    explicit Codex(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // CODEX_H
