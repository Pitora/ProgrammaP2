#include "additem.h"


void addItem::addControls(QFormLayout *layout)
{
     type = new QComboBox;
     effect = new QComboBox;
     atk_type = new QComboBox;

     type->addItem("Melee");
     type->addItem("Ranged");

     name = new QLineEdit;
     durability = new QLineEdit;
     weight = new QLineEdit;
     rarity = new QLineEdit;
     cost = new QLineEdit;
     raw_atk = new QLineEdit;
     crit = new QLineEdit;
     scStr = new QLineEdit;
     scDex = new QLineEdit;
     scAim = new QLineEdit;

     recoil = new QLineEdit;
     rld_time = new QLineEdit;
     magazine = new QLineEdit;

     save = new QPushButton("Save");

     effect->addItem("NO EFFECT");
     effect->addItem("BLEED");
     effect->addItem("FIRE");
     effect->addItem("POISON");
     effect->addItem("SLOW");
     effect->addItem("STONE");
     effect->addItem("THUNDER");
     effect->addItem("WATER");
     effect->addItem("WIND");

     atk_type->addItem("SLASH");
     atk_type->addItem("PIERCE");
     atk_type->addItem("STRIKE");

     durability->setValidator(new QIntValidator(0,100,this));
     durability->setPlaceholderText("Values between 0-100");

     weight->setValidator(new QIntValidator(0,100,this));
     weight->setPlaceholderText("Values between 0-100");

     rarity->setValidator(new QIntValidator(1,12,this));
     rarity->setPlaceholderText("Values between 1-12");

     cost->setValidator(new QIntValidator(0,99999,this));
     cost->setPlaceholderText("Values between 0-99999");

     raw_atk->setValidator(new QIntValidator(0,9999,this));
     raw_atk->setPlaceholderText("Values between 0-9999");

     crit->setValidator(new QIntValidator(0,100,this));
     crit->setPlaceholderText("Values between 0-100");

     scStr->setValidator(new QIntValidator(0,100,this));
     scStr->setPlaceholderText("Values between 0-100");

     scDex->setValidator(new QIntValidator(0,100,this));
     scDex->setPlaceholderText("Values between 0-100");

     scAim->setValidator(new QIntValidator(0,100,this));
     scAim->setPlaceholderText("Values between 0-100");

     recoil->setValidator(new QIntValidator(0,100,this));
     recoil->setPlaceholderText("Values between 0-100");

     rld_time->setValidator(new QIntValidator(0,15,this));
     rld_time->setPlaceholderText("Values between 0-15");

     magazine->setValidator(new QIntValidator(0,200,this));
     magazine->setPlaceholderText("Values between 0-200");

     layout->addRow("Type",type);
     layout->addRow("Name",name);
     layout->addRow("Weight",weight);
     layout->addRow("Rarity",rarity);
     layout->addRow("Cost",cost);
     layout->addRow("Raw Atk",raw_atk);
     layout->addRow("Crit %",crit);
     layout->addRow("Str scaling",scStr);
     layout->addRow("Dex scaling",scDex);
     layout->addRow("Aim Scaling",scAim);
     layout->addRow("Effect",effect);
     layout->addRow("Durability",durability);
     layout->addRow("Atk Type",atk_type);
     layout->addRow("Recoil",recoil);
     layout->addRow("Reload Time",rld_time);
     layout->addRow("Magazine",magazine);
     layout->addWidget(save);

     enableBox();

     connect(type,SIGNAL(currentIndexChanged(QString)),this,SLOT(enableBox()));
     connect(save,SIGNAL(clicked()),this,SLOT(saveItem()));
}

void addItem::addControlsArmor(QFormLayout *layout)
{
    defense = new QLineEdit;
    name = new QLineEdit;
    durability = new QLineEdit;
    resistance = new QComboBox;
    type = new QComboBox;

    save = new QPushButton("Save");

    type->addItem("HELM");
    type->addItem("CHEST");
    type->addItem("GLOVES");
    type->addItem("BOOTS");

    resistance->addItem("NO EFFECT");
    resistance->addItem("BLEED");
    resistance->addItem("FIRE");
    resistance->addItem("POISON");
    resistance->addItem("SLOW");
    resistance->addItem("STONE");
    resistance->addItem("THUNDER");
    resistance->addItem("WATER");
    resistance->addItem("WIND");

    defense->setValidator(new QIntValidator(0,9999,this));
    defense->setPlaceholderText("Values between 0-9999");

    durability->setValidator(new QIntValidator(0,100,this));
    durability->setPlaceholderText("Values between 0-100");

    layout->addRow("Type",type);
    layout->addRow("Name",name);
    layout->addRow("Defense",defense);
    layout->addRow("Durability",durability);
    layout->addRow("Resistance",resistance);
    layout->addWidget(save);

    connect(save,SIGNAL(clicked()),this,SLOT(saveItem()));

}

void addItem::addControlsConsumable(QFormLayout *layout)
{
    name = new QLineEdit;
    potency = new QLineEdit;
    duration = new QLineEdit;

    percentage = new QComboBox;
    effect = new QComboBox;
    type = new QComboBox;

    save = new QPushButton("Save");

    type->addItem("BUFF");
    type->addItem("HEALING");

    percentage->addItem("10");
    percentage->addItem("25");
    percentage->addItem("50");
    percentage->addItem("75");
    percentage->addItem("100");

    potency->setValidator(new QIntValidator(0,1000,this));
    potency->setPlaceholderText("Values between 0-1000");

    duration->setValidator(new QIntValidator(1,300,this));
    duration->setPlaceholderText("Values between 0-300");

    changeItem();

    layout->addRow("Type",type);
    layout->addRow("Effect",effect);
    layout->addRow("Potency",potency);
    layout->addRow("Percentage",percentage);
    layout->addRow("Duration",duration);
    layout->addWidget(save);

    connect(type,SIGNAL(currentIndexChanged(QString)),this,SLOT(changeItem()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveItem()));
}

addItem::addItem(int i, Controller* cont, QWidget *parent) : QDialog(parent){

    c = cont;

    QFormLayout* main = new QFormLayout;
    setLayout(main);

    if (i == 1){
        setWindowTitle("Create Weapon");
        addControls(main);
        setFixedSize(300,500);
    }else if (i == 2){
        setWindowTitle("Create Armor Piece");
        addControlsArmor(main);
        setFixedSize(300,200);
    }else if (i == 3){
        setWindowTitle("Create Consumable");
        addControlsConsumable(main);
        setFixedSize(300,200);
    }
}

void addItem::enableBox() const
{
    if(type->currentIndex() == 0){
        recoil->setEnabled(false);
        rld_time->setEnabled(false);
        magazine->setEnabled(false);
        effect->setEnabled(true);
        durability->setEnabled(true);
        atk_type->setEnabled(true);
    }else{
        recoil->setEnabled(true);
        rld_time->setEnabled(true);
        magazine->setEnabled(true);
        effect->setEnabled(false);
        durability->setEnabled(false);
        atk_type->setEnabled(false);
    }

    recoil->clear();
    rld_time->clear();
    magazine->clear();
}

void addItem::saveItem()
{
   close();
}

void addItem::changeItem(){
    if(type->currentIndex() == 0){
        effect->clear();
        effect->addItem("ATK UP");
        effect->addItem("DEF UP");
        effect->addItem("HP UP");
        effect->addItem("MP UP");
        effect->addItem("FIRE ATK UP");
        effect->addItem("THUNDER ATK UP");
        effect->addItem("WATER ATK UP");
        effect->addItem("WIND ATK UP");
        effect->addItem("FIRE RES UP");
        effect->addItem("THUNDER RES UP");
        effect->addItem("WATER RES UP");
        effect->addItem("WIND RES UP");
        effect->addItem("ALL STATS UP");
        effect->addItem("POISON RES UP");
        effect->addItem("BLEED RES UP");
        potency->setEnabled(false);
        duration->setEnabled(true);
        percentage->setEnabled(true);

    }else{
        effect->clear();
        effect->addItem("RECOVER HP");
        effect->addItem("RECOVER MP");
        effect->addItem("RECOVER STA");
        duration->setEnabled(false);
        percentage->setEnabled(false);
        potency->setEnabled(true);
    }
}
