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
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpacerItem>
#include <QFileDialog>
#include <utility>
#include "smartcombobox.h"

class Controller;

class Window : public QWidget
{
    Q_OBJECT
private:

    QMenu* file;
    QMenu* create;

    QPushButton* import;
    QPushButton* save;

    SmartComboBox* weapon_box;
    SmartComboBox* helm_box;
    SmartComboBox* chest_box;
    SmartComboBox* gloves_box;
    SmartComboBox* boots_box;
    SmartComboBox* item1_box;
    SmartComboBox* item2_box;
    SmartComboBox* item3_box;

    QLineEdit* build_name;
    QLabel* atk_lbl;
    QLabel* def_lbl;

    QLabel* vit_lbl;
    QLabel* str_lbl;
    QLabel* dex_lbl;
    QLabel* aim_lbl;

    QLineEdit* vit_text;
    QLineEdit* str_text;
    QLineEdit* dex_text;
    QLineEdit* aim_text;

    Controller* controller;

    void addMenu(QVBoxLayout *layout);
    void addCommand(QVBoxLayout *layout);
    void addLabel(QHBoxLayout* layout);
    void addButton(QVBoxLayout* layout);


public:

    Window(QWidget *parent = 0);
    QString exportCharDialog();
    QString importCharDialog();
    void setController(Controller *c);
    void calcDmgDef(int a, int d);
    void loadBox(QList<QString> n, QList<int> id, int i);
    void setBuildName(QString s);
    void setStats(QList<QString> l);
    void setWeapon(int s);
    void setArmor(QList<int> l);
    void setItems(QList<int> l);

    ~Window();

};

#endif // WINDOW_H
