#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QString>
#include <QComboBox>
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpacerItem>
#include <QFileDialog>
#include <utility>
#include <QTextEdit>
#include "smartcombobox.h"
#include "windowtabwidget.h"


class Controller;

class Window : public QWidget
{
    Q_OBJECT
private:

    QMenu* file;
    QMenu* create;

    QPushButton* import;
    QPushButton* exp;
    QPushButton* def;
    QPushButton* del;

    QTextEdit* compareBox1;

    QTabWidget* tab;
    QListWidget* characters;

    Controller* controller;

    void addMenu(QVBoxLayout *layout);

    void addCommand(QVBoxLayout *layout);
    void addLabel(QHBoxLayout* layout);
    void addButton(QVBoxLayout* layout);

public slots:
    void addTab(QListWidgetItem* i);
    void closeTab(int index);

public:

    Window(QWidget *parent = 0);

    QString exportCharDialog();
    QString importCharDialog();

    void setController(Controller *c);

    int getIndSelChar();

    void refreshCompare(QString c1, QString c2,QString op);

    void calcDmgDef(int a, int d);
    void loadBox(QList<QString> n, QList<int> id, int i);
    void setBuildName(QString s);
    void setStats(QList<QString> l);
    void setWeapon(int s);
    void setArmor(QList<int> l);
    void setItems(QList<int> l);

    void removeTab(int index);
    void refresh();

    ~Window();

};

#endif // WINDOW_H
