#include "windowtabwidget.h"
#include "controller/controller.h"

windowtabwidget::windowtabwidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* main = new QHBoxLayout;
    addCommand(main);
    setLayout(main);
}

void windowtabwidget::addCommand(QHBoxLayout *layout)
{
    QVBoxLayout* layoutCharacter = new QVBoxLayout;
    layout->addLayout(layoutCharacter);

    weapon_box = new SmartComboBox(this);
    helm_box = new SmartComboBox(this);
    chest_box = new SmartComboBox(this);
    gloves_box = new SmartComboBox(this);
    boots_box = new SmartComboBox(this);
    item1_box = new SmartComboBox(this);
    item2_box = new SmartComboBox(this);
    item3_box = new SmartComboBox(this);


    weapon_box->setMinimumWidth(250);
    helm_box->setMinimumWidth(250);
    chest_box->setMinimumWidth(250);
    gloves_box->setMinimumWidth(250);
    boots_box->setMinimumWidth(250);
    item1_box->setMinimumWidth(250);
    item2_box->setMinimumWidth(250);
    item3_box->setMinimumWidth(250);

    weapon_box->setFont(QFont("Ubuntu",15));
    helm_box->setFont(QFont("Ubuntu",15));
    chest_box->setFont(QFont("Ubuntu",15));
    gloves_box->setFont(QFont("Ubuntu",15));
    boots_box->setFont(QFont("Ubuntu",15));
    item1_box->setFont(QFont("Ubuntu",15));
    item2_box->setFont(QFont("Ubuntu",15));
    item3_box->setFont(QFont("Ubuntu",15));

    weapon_box->setStyleSheet("QComboBox{selection-background-color : grey}");
    helm_box->setStyleSheet("QComboBox{selection-background-color : grey}");
    chest_box->setStyleSheet("QComboBox{selection-background-color : grey}");
    gloves_box->setStyleSheet("QComboBox{selection-background-color : grey}");
    boots_box->setStyleSheet("QComboBox{selection-background-color : grey}");
    item1_box->setStyleSheet("QComboBox{selection-background-color : grey}");
    item2_box->setStyleSheet("QComboBox{selection-background-color : grey}");
    item3_box->setStyleSheet("QComboBox{selection-background-color : grey}");

    QLabel* weap_lb = new QLabel("Weapon");
    QLabel* helm_lb = new QLabel("Helm");
    QLabel* chest_lb = new QLabel("Chest");
    QLabel* gloves_lb = new QLabel("Gloves");
    QLabel* boots_lb = new QLabel("Boots");
    QLabel* item1_lb = new QLabel("Item1");
    QLabel* item2_lb = new QLabel("Item2");
    QLabel* item3_lb = new QLabel("Item3");

    weap_lb->setFont(QFont("Ubuntu",15));
    helm_lb->setFont(QFont("Ubuntu",15));
    chest_lb->setFont(QFont("Ubuntu",15));
    gloves_lb->setFont(QFont("Ubuntu",15));
    boots_lb->setFont(QFont("Ubuntu",15));
    item1_lb->setFont(QFont("Ubuntu",15));
    item2_lb->setFont(QFont("Ubuntu",15));
    item3_lb->setFont(QFont("Ubuntu",15));

    layoutCharacter->addWidget(weap_lb);
    layoutCharacter->addWidget(weapon_box);
    layoutCharacter->addWidget(helm_lb);
    layoutCharacter->addWidget(helm_box);
    layoutCharacter->addWidget(chest_lb);
    layoutCharacter->addWidget(chest_box);
    layoutCharacter->addWidget(gloves_lb);
    layoutCharacter->addWidget(gloves_box);
    layoutCharacter->addWidget(boots_lb);
    layoutCharacter->addWidget(boots_box);
    layoutCharacter->addWidget(item1_lb);
    layoutCharacter->addWidget(item1_box);
    layoutCharacter->addWidget(item2_lb);
    layoutCharacter->addWidget(item2_box);
    layoutCharacter->addWidget(item3_lb);
    layoutCharacter->addWidget(item3_box);

    connect(weapon_box,SIGNAL(highlighted(int)),this,SLOT(changeWeaponImage(int)));
    connect(helm_box,SIGNAL(highlighted(int)),this,SLOT(changeHelmImage(int)));
    connect(chest_box,SIGNAL(highlighted(int)),this,SLOT(changeChestImage(int)));
    connect(gloves_box,SIGNAL(highlighted(int)),this,SLOT(changeGlovesImage(int)));
    connect(boots_box,SIGNAL(highlighted(int)),this,SLOT(changeBootsImage(int)));
    connect(item1_box,SIGNAL(highlighted(int)),this,SLOT(changeItem1Image(int)));
    connect(item2_box,SIGNAL(highlighted(int)),this,SLOT(changeItem2Image(int)));
    connect(item3_box,SIGNAL(highlighted(int)),this,SLOT(changeItem3Image(int)));

    addLabel(layout);
}

void windowtabwidget::addLabel(QHBoxLayout *layout)
{

    char_lbl  = new QLabel();
    layout->addStretch(50);
    layout->addWidget(char_lbl);
    layout->addStretch(50);

    char_lbl->setPixmap(QPixmap("assets/b_char"));
    char_lbl->setScaledContents(true);
    char_lbl->setMaximumSize(400,500);

    QVBoxLayout* statLayout = new QVBoxLayout();
    statLayout->setSpacing(10);
    layout->addLayout(statLayout);
    build_name = new QLineEdit();
    statLayout->addWidget(build_name);

    statLayout->setMargin(50);

    build_name->setPlaceholderText("Build Name");
    build_name->setMaximumWidth(200);
    build_name->setFont(QFont("Ubuntu",15));
    build_name->setStyleSheet(" background-color : rgb(241,217,156)");

    vit_lbl = new QLabel("VIT ");
    str_lbl = new QLabel("STR ");
    dex_lbl = new QLabel("DEX ");
    aim_lbl = new QLabel("AIM ");

    vit_lbl->setFont(QFont("Ubuntu",15));
    str_lbl->setFont(QFont("Ubuntu",15));
    dex_lbl->setFont(QFont("Ubuntu",15));
    aim_lbl->setFont(QFont("Ubuntu",15));

    vit_text = new QLineEdit();
    str_text = new QLineEdit();
    dex_text = new QLineEdit();
    aim_text = new QLineEdit();

    vit_text->setFont(QFont("Ubuntu",15));
    str_text->setFont(QFont("Ubuntu",15));
    dex_text->setFont(QFont("Ubuntu",15));
    aim_text->setFont(QFont("Ubuntu",15));

    vit_lbl->setFixedWidth(50);
    str_lbl->setFixedWidth(50);
    dex_lbl->setFixedWidth(50);
    aim_lbl->setFixedWidth(50);

    vit_text->setStyleSheet(" background-color : rgb(241,217,156)");
    str_text->setStyleSheet(" background-color : rgb(241,217,156)");
    dex_text->setStyleSheet(" background-color : rgb(241,217,156)");
    aim_text->setStyleSheet(" background-color : rgb(241,217,156)");

    vit_text->setMaximumSize(50,30);
    str_text->setMaximumSize(50,30);
    dex_text->setMaximumSize(50,30);
    aim_text->setMaximumSize(50,30);

    QHBoxLayout* vitL = new QHBoxLayout();
    statLayout->addLayout(vitL);
    QLabel* v_icon = new QLabel();
    v_icon->setPixmap(QPixmap("assets/viticon.png"));
    v_icon->setScaledContents(true);
    v_icon->setFixedSize(40,40);
    vitL->addWidget(v_icon);
    vitL->addWidget(vit_lbl);
    vitL->addWidget(vit_text);
    QLabel* a = new QLabel("Affect the DEF");
    a->setFont(QFont("Ubuntu",15));
    vitL->addWidget(a);

    QHBoxLayout* strL = new QHBoxLayout();
    statLayout->addLayout(strL);
    QLabel* s_icon = new QLabel();
    s_icon->setPixmap(QPixmap("assets/stricon.png"));
    s_icon->setScaledContents(true);
    s_icon->setFixedSize(40,40);
    strL->addWidget(s_icon);
    strL->addWidget(str_lbl);
    strL->addWidget(str_text);
    QLabel* b = new QLabel("Affect the ATK with heavy weapons");
    b->setFont(QFont("Ubuntu",15));
    strL->addWidget(b);

    QHBoxLayout* dexL = new QHBoxLayout();
    statLayout->addLayout(dexL);
    QLabel* d_icon = new QLabel();
    d_icon->setPixmap(QPixmap("assets/dexicon.png"));
    d_icon->setScaledContents(true);
    d_icon->setFixedSize(40,40);
    dexL->addWidget(d_icon);
    dexL->addWidget(dex_lbl);
    dexL->addWidget(dex_text);
    QLabel* c = new QLabel("Affect the ATK with light weapons");
    c->setFont(QFont("Ubuntu",15));
    dexL->addWidget(c);

    QHBoxLayout* aimL = new QHBoxLayout();
    statLayout->addLayout(aimL);
    QLabel* a_icon = new QLabel();
    a_icon->setPixmap(QPixmap("assets/aimicon.png"));
    a_icon->setScaledContents(true);
    a_icon->setFixedSize(40,40);
    aimL->addWidget(a_icon);
    aimL->addWidget(aim_lbl);
    aimL->addWidget(aim_text);
    QLabel* d = new QLabel("Affect the ATK with ranged weapons");
    d->setFont(QFont("Ubuntu",15));
    aimL->addWidget(d);

    vit_text->setValidator(new QIntValidator(0,9999,this));
    str_text->setValidator(new QIntValidator(0,9999,this));
    dex_text->setValidator(new QIntValidator(0,9999,this));
    aim_text->setValidator(new QIntValidator(0,9999,this));

    QHBoxLayout* atkLayout = new QHBoxLayout();
    statLayout->addLayout(atkLayout);

    atk_lbl = new QLabel("ATK ");
    QLabel* atk_icon = new QLabel();
    atk_icon->setPixmap(QPixmap("assets/atkicon.png"));
    atk_icon->setScaledContents(true);
    atk_icon->setFixedSize(50,50);
    atkLayout->addWidget(atk_icon);
    atkLayout->addWidget(atk_lbl);


    def_lbl = new QLabel("DEF ");
    atk_lbl->setFont(QFont("Ubuntu",30));
    def_lbl->setFont(QFont("Ubuntu",30));
    QHBoxLayout* defLayout = new QHBoxLayout();
    statLayout->addLayout(defLayout);
    QLabel* def_icon = new QLabel();
    def_icon->setPixmap(QPixmap("assets/deficon.png"));
    def_icon->setScaledContents(true);
    def_icon->setFixedSize(50,50);
    defLayout->addWidget(def_icon);
    defLayout->addWidget(def_lbl);

    optimize = new QPushButton("Optimize");

    statLayout->insertSpacing(7,20);
    statLayout->addWidget(optimize);
    optimize->setFont(QFont("Ubuntu",15));
    optimize->setFixedWidth(100);

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


    connect(optimize,SIGNAL(clicked()),controller,SLOT(optimize()));
}

//imposta l'attacco e la difesa
void windowtabwidget::calcDmgDef(int a, int d)
{
    atk_lbl->setText("ATK  " + QString::number(a));
    def_lbl->setText("DEF  " + QString::number(d));
}

//carica le combobox
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

//imposta il nome della build
void windowtabwidget::setBuildName(QString s){ build_name->setText(s);}

//imposta le stat della build
void windowtabwidget::setStats(QList<QString> l)
{
    vit_text->setText(l[0]);
    str_text->setText(l[1]);
    dex_text->setText(l[2]);
    aim_text->setText(l[3]);
}

//imposta l'arma della build
void windowtabwidget::setWeapon(int s){weapon_box->setCurrentIndex(weapon_box->findData(s));}

//imposta i pezzi di equipaggiamento della build
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

//imposta gli oggetti della build
void windowtabwidget::setItems(QList<int> l)
{
    item1_box->setCurrentIndex(item1_box->findData(l[0]));
    item2_box->setCurrentIndex(item2_box->findData(l[1]));
    item3_box->setCurrentIndex(item3_box->findData(l[2]));
}

void windowtabwidget::resetImage()
{
    char_lbl->setPixmap(QPixmap("assets/b_char.png"));
}

void windowtabwidget::changeWeaponImage(int)
{
    char_lbl->setPixmap(QPixmap("assets/redsword_char.png"));
}

void windowtabwidget::changeHelmImage(int)
{
    char_lbl->setPixmap(QPixmap("assets/redhelm_char.png"));
}

void windowtabwidget::changeChestImage(int)
{
    char_lbl->setPixmap(QPixmap("assets/redchest_char.png"));
}

void windowtabwidget::changeGlovesImage(int)
{
    char_lbl->setPixmap(QPixmap("assets/redgloves_char.png"));
}

void windowtabwidget::changeBootsImage(int)
{
    char_lbl->setPixmap(QPixmap("assets/redboots_char.png"));
}

void windowtabwidget::changeItem1Image(int)
{
    char_lbl->setPixmap(QPixmap("assets/reditem1_char.png"));
}

void windowtabwidget::changeItem2Image(int)
{
    char_lbl->setPixmap(QPixmap("assets/reditem2_char.png"));
}

void windowtabwidget::changeItem3Image(int)
{
    char_lbl->setPixmap(QPixmap("assets/reditem3_char.png"));
}

void windowtabwidget::setId(int i){id = i;}

int windowtabwidget::getId(){ return id;}







