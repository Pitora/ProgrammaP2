#ifndef WINDOWTABWIDGET_H
#define WINDOWTABWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <utility>
#include "smartcombobox.h"

class Controller;

class windowtabwidget : public QWidget
{
    Q_OBJECT
public:
    explicit windowtabwidget(QWidget *parent = nullptr);

    void setController(Controller *c);

    void calcDmgDef(int a, int d);
    void loadBox(QList<QString> n, QList<int> id, int i);

    void setBuildName(QString s);
    void setStats(QList<QString> l);
    void setWeapon(int s);
    void setArmor(QList<int> l);
    void setItems(QList<int> l);

    void resetImage();

    void setId(int i);
    int getId();

signals:

public slots:
    void changeWeaponImage(int);
    void changeHelmImage(int);
    void changeChestImage(int);
    void changeGlovesImage(int);
    void changeBootsImage(int);
    void changeItem1Image(int);
    void changeItem2Image(int);
    void changeItem3Image(int);

private:

    int id;

    SmartComboBox* weapon_box;
    SmartComboBox* helm_box;
    SmartComboBox* chest_box;
    SmartComboBox* gloves_box;
    SmartComboBox* boots_box;
    SmartComboBox* item1_box;
    SmartComboBox* item2_box;
    SmartComboBox* item3_box;

    QPushButton* optimize;

    QLineEdit* build_name;
    QLabel* atk_lbl;
    QLabel* def_lbl;

    QLabel* vit_lbl;
    QLabel* str_lbl;
    QLabel* dex_lbl;
    QLabel* aim_lbl;

    QLabel* char_lbl;

    QLineEdit* vit_text;
    QLineEdit* str_text;
    QLineEdit* dex_text;
    QLineEdit* aim_text;

    Controller* controller;

    void addCommand(QHBoxLayout *layout);

    void addLabelChar(QHBoxLayout* layout);

    void addStatsCommands(QHBoxLayout* layout);

    void addParamCommands(QVBoxLayout* layout);

    void setLblAndTxt();
};

#endif // WINDOWTABWIDGET_H
