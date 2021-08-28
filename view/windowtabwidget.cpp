#include "windowtabwidget.h"
#include "controller/controller.h"

windowtabwidget::windowtabwidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* main = new QVBoxLayout;
    addCommand(main);
    setLayout(main);
    //setMinimumSize(1024,600);
}

void windowtabwidget::addCommand(QVBoxLayout *layout)
{
    QHBoxLayout* hLayout = new QHBoxLayout;
    QFormLayout* form = new QFormLayout;

    layout->addLayout(hLayout);
    hLayout->addLayout(form);

    form->setRowWrapPolicy(QFormLayout::WrapAllRows);
    form->setVerticalSpacing(10);
    form->setContentsMargins(11,20,0,0);

    weapon_box = new SmartComboBox(this);
    helm_box = new SmartComboBox(this);
    chest_box = new SmartComboBox(this);
    gloves_box = new SmartComboBox(this);
    boots_box = new SmartComboBox(this);
    item1_box = new SmartComboBox(this);
    item2_box = new SmartComboBox(this);
    item3_box = new SmartComboBox(this);

    weapon_box->setFixedWidth(250);
    helm_box->setFixedWidth(250);
    chest_box->setFixedWidth(250);
    gloves_box->setFixedWidth(250);
    boots_box->setFixedWidth(250);
    item1_box->setFixedWidth(250);
    item2_box->setFixedWidth(250);
    item3_box->setFixedWidth(250);

    form->addRow("Weapon",weapon_box);
    form->addRow("Helm",helm_box);
    form->addRow("Chest",chest_box);
    form->addRow("Gloves",gloves_box);
    form->addRow("Boots",boots_box);
    form->addRow("Item1",item1_box);
    form->addRow("Item2",item2_box);
    form->addRow("Item3",item3_box);

    hLayout->addSpacing(200);

    addLabel(hLayout);
}

void windowtabwidget::addLabel(QHBoxLayout *layout)
{
    QFormLayout* midLayout = new QFormLayout;
    QFormLayout* rightLayout = new QFormLayout;

    midLayout->setContentsMargins(11,20,0,0);
    layout->addLayout(midLayout);
    layout->addLayout(rightLayout);
    midLayout->setSpacing(30);

    build_name = new QLineEdit();
    atk_lbl = new QLabel();
    def_lbl = new QLabel();
    vit_lbl = new QLabel();
    str_lbl = new QLabel();
    dex_lbl = new QLabel();
    aim_lbl = new QLabel();

    vit_text = new QLineEdit();
    str_text = new QLineEdit();
    dex_text = new QLineEdit();
    aim_text = new QLineEdit();

    build_name->setPlaceholderText("Build Name");
    QPalette pal = build_name->palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window));
    build_name->setPalette(pal);
    build_name->setFrame(QFrame::NoFrame);
    build_name->setFixedWidth(200);
    atk_lbl->setText("ATK : ");
    def_lbl->setText("DEF : ");

    vit_text->setMaximumWidth(70);
    str_text->setMaximumWidth(70);
    dex_text->setMaximumWidth(70);
    aim_text->setMaximumWidth(70);

    vit_text->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    str_text->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    dex_text->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    aim_text->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    vit_text->setValidator(new QIntValidator(0,9999,this));
    str_text->setValidator(new QIntValidator(0,9999,this));
    dex_text->setValidator(new QIntValidator(0,9999,this));
    aim_text->setValidator(new QIntValidator(0,9999,this));

    vit_text->setFrame(false);
    str_text->setFrame(false);
    dex_text->setFrame(false);
    aim_text->setFrame(false);

    midLayout->addWidget(build_name);
    midLayout->addRow("VIT : ", vit_text);
    midLayout->addRow("STR : ", str_text);
    midLayout->addRow("DEX : ", dex_text);
    midLayout->addRow("AIM : ", aim_text);
    midLayout->addWidget(atk_lbl);
    midLayout->addWidget(def_lbl);

    vit_lbl->setText("Affect the DEF");
    str_lbl->setText("Affect the ATK with heavy weapons");
    dex_lbl->setText("Affect the ATK with light weapons");
    aim_lbl->setText("Affect the ATK with ranged weapons");


    QSpacerItem* space = new QSpacerItem(17,20);
    rightLayout->setContentsMargins(11,20,0,0);
    rightLayout->setSpacing(35);
    rightLayout->addItem(space);
    rightLayout->addRow(vit_lbl);
    rightLayout->addRow(str_lbl);
    rightLayout->addRow(dex_lbl);
    rightLayout->addRow(aim_lbl);

}

void windowtabwidget::setController(Controller *c)
{
    controller = c;

    connect(vit_text,SIGNAL(textChanged(QString)),controller,SLOT(setVitality(QString)));
    connect(str_text,SIGNAL(textChanged(QString)),controller,SLOT(setStrenght(QString)));
    connect(dex_text,SIGNAL(textChanged(QString)),controller,SLOT(setDexterity(QString)));
    connect(aim_text,SIGNAL(textChanged(QString)),controller,SLOT(setAim(QString)));

    connect(build_name,SIGNAL(textChanged(QString)),controller,SLOT(changeName(QString)));

    connect(weapon_box,SIGNAL(activated(QVariant)),controller,SLOT(changeWeapon(QVariant)));
    connect(helm_box,SIGNAL(activated(QVariant)),controller,SLOT(changeArmor(QVariant)));
    connect(chest_box,SIGNAL(activated(QVariant)),controller,SLOT(changeArmor(QVariant)));
    connect(gloves_box,SIGNAL(activated(QVariant)),controller,SLOT(changeArmor(QVariant)));
    connect(boots_box,SIGNAL(activated(QVariant)),controller,SLOT(changeArmor(QVariant)));
    connect(item1_box,SIGNAL(activated(QVariant)),controller,SLOT(changeItem1(QVariant)));
    connect(item2_box,SIGNAL(activated(QVariant)),controller,SLOT(changeItem2(QVariant)));
    connect(item3_box,SIGNAL(activated(QVariant)),controller,SLOT(changeItem3(QVariant)));
}

void windowtabwidget::calcDmgDef(int a, int d)
{
    atk_lbl->setText("ATK : " + QString::number(a));
    def_lbl->setText("DEF : " + QString::number(d));
}

void windowtabwidget::loadBox(QList<QString> n, QList<int> id, int i)
{
    switch (i) {
    case 1:
        weapon_box->clear();
        for(int j = 0; j< n.size(); j++){
            weapon_box->addItem(n.at(j),id.at(j));
        }
        break;
    case 2:
        helm_box->clear();
        for(int j = 0; j< n.size(); j++){
            helm_box->addItem(n.at(j),id.at(j));
        }
        break;
    case 3:
        chest_box->clear();
        for(int j = 0; j< n.size(); j++){
            chest_box->addItem(n.at(j),id.at(j));
        }
        break;
    case 4:
        gloves_box->clear();
        for(int j = 0; j< n.size(); j++){
            gloves_box->addItem(n.at(j),id.at(j));
        }
        break;
    case 5:
        boots_box->clear();
        for(int j = 0; j< n.size(); j++){
            boots_box->addItem(n.at(j),id.at(j));
        }
        break;
    case 6:
        item1_box->clear();
        item2_box->clear();
        item3_box->clear();
        for(int j = 0; j< n.size(); j++){
            item1_box->addItem(n.at(j),id.at(j));
            item2_box->addItem(n.at(j),id.at(j));
            item3_box->addItem(n.at(j),id.at(j));
        }
        break;
    default:
        break;
    }
}

void windowtabwidget::setBuildName(QString s){ build_name->setText(s);}

void windowtabwidget::setStats(QList<QString> l)
{
    vit_text->setText(l[0]);
    str_text->setText(l[1]);
    dex_text->setText(l[2]);
    aim_text->setText(l[3]);
}

void windowtabwidget::setWeapon(int s){weapon_box->setCurrentIndex(weapon_box->findData(s));}

void windowtabwidget::setArmor(QList<int> l)
{
    for(auto i = l.begin(); i != l.end(); ++i){
        if(helm_box->findData(*i) != -1){
            helm_box->setCurrentIndex(helm_box->findData(*i));
        }
        if(chest_box->findData(*i) != -1){
            chest_box->setCurrentIndex(chest_box->findData(*i));
        }
        if(gloves_box->findData(*i) != -1){
            gloves_box->setCurrentIndex(gloves_box->findData(*i));
        }
        if(boots_box->findData(*i) != -1){
            boots_box->setCurrentIndex(boots_box->findData(*i));
        }
    }
}

void windowtabwidget::setItems(QList<int> l)
{
    item1_box->setCurrentIndex(item1_box->findData(l[0]));
    item2_box->setCurrentIndex(item2_box->findData(l[1]));
    item3_box->setCurrentIndex(item3_box->findData(l[2]));
}

void windowtabwidget::setId(int i){id = i;}

int windowtabwidget::getId(){ return id;}
