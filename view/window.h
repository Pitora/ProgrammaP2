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
#include <QFileDialog>
#include <QCheckBox>
#include <utility>
#include <QTextEdit>
#include <QMessageBox>
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
    QTextEdit* compareBox2;

    QTabWidget* tab;
    QListWidget* characters;

    QCheckBox* comp;

    Controller* controller;

    QCursor* curs;

    void addMenu(QHBoxLayout *layout);

    void addCommand(QHBoxLayout *layout);

public slots:
    void addTab(QListWidgetItem* i);
    void closeTab(int index);
    void lockCompare(bool clicked);

public:

    Window(QWidget *parent = 0);

    QString exportCharDialog();
    QString importCharDialog();

    void setController(Controller *c);
    void showMessage(QString wrn);

    int getIndSelChar();
    bool getCheckValue();

    void refreshCompare(QList<QString> list);
    void clearCompare();

    void calcDmgDef(int a, int d);
    void loadBox(QList<QString> n, QList<int> id, int i);
    void setBuildName(QString s);
    void setStats(QList<QString> l);
    void setWeapon(int s);
    void setArmor(QList<int> l);
    void setItems(QList<int> l);

    void setWithColor(QString s,QColor color);

    void setTabName(QString s);
    void refresh();

    ~Window();

};

#endif // WINDOW_H
