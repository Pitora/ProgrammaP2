#ifndef ADDITEM_H
#define ADDITEM_H

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

class addItem : public QDialog
{
    Q_OBJECT
private:

    Controller* c;

    QComboBox* type;            //usato su weapon,armor e consumable
    QComboBox* effect;          //usato su weapon,armor e consumable
    QComboBox* atk_type;

    QComboBox* resistance;
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

    void addControls(QFormLayout* layout);
    void addControlsArmor(QFormLayout* layout);
    void addControlsConsumable(QFormLayout* layout);

public:
    explicit addItem(int i,Controller* cont,QWidget *parent = nullptr);

signals:

public slots:
    void enableBox() const;
    void changeItem();
    void saveItem() ;

};

#endif // ADDITEM_H
