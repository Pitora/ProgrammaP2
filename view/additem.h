#ifndef ADDITEM_H
#define ADDITEM_H

#include "controller/controller.h"
#include "window.h"

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <utility>

class Controller;

class AddItem : public QDialog
{
    Q_OBJECT
private:

    Controller* c;

    QComboBox* type;            //usato su weapon,armor e consumable
    QComboBox* effect;          //usato su weapon,armor e consumable
    QComboBox* atk_type;

    QComboBox* armor_piece;

    QComboBox* percentage;

    QLineEdit* name;            //usato su weapon,armor e consumable
    QLineEdit* durability;      //usato su weapon,armor
    QLineEdit* weight;
    QLineEdit* rarity;
    QLineEdit* cost;
    QLineEdit* raw_atk;
    QLineEdit* crit;
    QLineEdit* scStr;
    QLineEdit* scDex;
    QLineEdit* scAim;

    QLineEdit* recoil;
    QLineEdit* rld_time;
    QLineEdit* magazine;

    QLineEdit* defense;

    QLineEdit* duration;
    QLineEdit* potency;

    QPushButton* save;

    void addControlsWeapon(QFormLayout* layout);
    void addControlsArmor(QFormLayout* layout);
    void addControlsConsumable(QFormLayout* layout);

    void addEffect();
    void addItemEffect(QString s);


public:
    explicit AddItem(int i,Controller* cont,QWidget *parent = nullptr);

signals:

public slots:
    void enableBox();
    void changeItem();
    void getArmorData();
    void getWeaponData();
    void getConsumableData();
};

#endif // ADDITEM_H
