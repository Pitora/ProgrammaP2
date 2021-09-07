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

    QLabel* weap_lb = new QLabel("Weapon");
    QLabel* helm_lb = new QLabel("Helm");
    QLabel* chest_lb = new QLabel("Chest");
    QLabel* gloves_lb = new QLabel("Gloves");
    QLabel* boots_lb = new QLabel("Boots");
    QLabel* item1_lb = new QLabel("Item1");
    QLabel* item2_lb = new QLabel("Item2");
    QLabel* item3_lb = new QLabel("Item3");

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

    layoutCharacter->

    connect(weapon_box,SIGNAL(highlighted(int)),this,SLOT(changeImage(int)));
    connect(helm_box,SIGNAL(highlighted(int)),this,SLOT(changeImage(int)));
    connect(chest_box,SIGNAL(highlighted(int)),this,SLOT(changeImage(int)));
    connect(gloves_box,SIGNAL(highlighted(int)),this,SLOT(changeImage(int)));
    connect(boots_box,SIGNAL(highlighted(int)),this,SLOT(changeImage(int)));
    connect(item1_box,SIGNAL(highlighted(int)),this,SLOT(changeImage(int)));
    connect(item2_box,SIGNAL(highlighted(int)),this,SLOT(changeImage(int)));
    connect(item3_box,SIGNAL(highlighted(int)),this,SLOT(changeImage(int)));

    addLabel(layout);
}

void windowtabwidget::addLabel(QHBoxLayout *layout)
{

    layout->setMargin(30);
    char_lbl  = new QLabel();
    layout->addStretch(50);
    layout->addWidget(char_lbl);
    layout->addStretch(50);


    char_lbl->setPixmap(QPixmap("assets/b_char"));
    char_lbl->setScaledContents(true);
    char_lbl->setMaximumSize(400,500);


    QVBoxLayout* statLayout = new QVBoxLayout();
    layout->addLayout(statLayout);
    build_name = new QLineEdit();
    statLayout->addWidget(build_name);

    statLayout->setMargin(50);

    build_name->setPlaceholderText("Build Name");
    build_name->setMaximumWidth(200);
    build_name->setFrame(QFrame::NoFrame);

    vit_lbl = new QLabel("VIT : ");
    str_lbl = new QLabel("STR : ");
    dex_lbl = new QLabel("DEX : ");
    aim_lbl = new QLabel("AIM : ");

    vit_text = new QLineEdit();
    str_text = new QLineEdit();
    dex_text = new QLineEdit();
    aim_text = new QLineEdit();

    vit_lbl->setFixedWidth(40);
    str_lbl->setFixedWidth(40);
    dex_lbl->setFixedWidth(40);
    aim_lbl->setFixedWidth(40);

    vit_text->setMaximumSize(50,30);
    str_text->setMaximumSize(50,30);
    dex_text->setMaximumSize(50,30);
    aim_text->setMaximumSize(50,30);

    QHBoxLayout* vitL = new QHBoxLayout();
    statLayout->addLayout(vitL);
    vitL->addWidget(vit_lbl);
    vitL->addWidget(vit_text);
    vitL->addWidget(new QLabel("Affect the DEF"));

    QHBoxLayout* strL = new QHBoxLayout();
    statLayout->addLayout(strL);
    strL->addWidget(str_lbl);
    strL->addWidget(str_text);
    strL->addWidget(new QLabel("Affect the ATK with heavy weapons"));

    QHBoxLayout* dexL = new QHBoxLayout();
    statLayout->addLayout(dexL);
    dexL->addWidget(dex_lbl);
    dexL->addWidget(dex_text);
    dexL->addWidget(new QLabel("Affect the ATK with light weapons"));

    QHBoxLayout* aimL = new QHBoxLayout();
    statLayout->addLayout(aimL);
    aimL->addWidget(aim_lbl);
    aimL->addWidget(aim_text);
    aimL->addWidget(new QLabel("Affect the ATK with Ranged weapons"));

    vit_text->setValidator(new QIntValidator(0,9999,this));
    str_text->setValidator(new QIntValidator(0,9999,this));
    dex_text->setValidator(new QIntValidator(0,9999,this));
    aim_text->setValidator(new QIntValidator(0,9999,this));
    vit_text->setFrame(false);
    str_text->setFrame(false);
    dex_text->setFrame(false);
    aim_text->setFrame(false);

    QVBoxLayout* atkLayout = new QVBoxLayout();
    statLayout->addLayout(atkLayout);

    atk_lbl = new QLabel("ATK : ");
    def_lbl = new QLabel("DEF : ");

    atk_lbl->setMaximumWidth(150);
    def_lbl->setMaximumWidth(150);

    atkLayout->addWidget(atk_lbl);
    atkLayout->addWidget(def_lbl);
    //atkLayout->setAlignment(atk_lbl,Qt::AlignLeft);
    //atkLayout->setAlignment(def_lbl,Qt::AlignLeft);

    optimize = new QPushButton("Optimize");

    statLayout->addWidget(optimize);
    optimize->setFixedWidth(100);

    //statLayout->setAlignment(optimize,Qt::AlignLeft);

    /*descLayout->addWidget(new QLabel("Affect the DEF"));
    descLayout->addWidget(new QLabel("Affect the ATK with heavy weapons"));
    descLayout->addWidget(new QLabel("Affect the ATK with light weapons"));
    descLayout->addWidget(new QLabel("Affect the ATK with ranged weapons"));


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

    optimize = new QPushButton("Optimize");
    midLayout->addWidget(optimize);

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
*/


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
    atk_lbl->setText("ATK : " + QString::number(a));
    def_lbl->setText("DEF : " + QString::number(d));
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

void windowtabwidget::changeImage(int)
{
    QWidget* q = this->focusWidget();
    if(q == weapon_box)
    {
        char_lbl->setPixmap(QPixmap("assets/redsword_char.png"));
    }
    else if(q == helm_box)
    {
        char_lbl->setPixmap(QPixmap("assets/redhelm_char.png"));
    }
    else if (q == chest_box)
    {
        char_lbl->setPixmap(QPixmap("assets/redchest_char.png"));
    }
    else if (q == gloves_box)
    {
        char_lbl->setPixmap(QPixmap("assets/redgloves_char.png"));
    }
    else if (q == boots_box)
    {
        char_lbl->setPixmap(QPixmap("assets/redboots_char.png"));
    }
    else if (q == item1_box)
    {
        char_lbl->setPixmap(QPixmap("assets/reditem1_char.png"));
    }
    else if(q == item2_box)
    {
        char_lbl->setPixmap(QPixmap("assets/reditem2_char.png"));
    }
    else if (q == item3_box)
    {
        char_lbl->setPixmap(QPixmap("assets/reditem3_char.png"));
    }
}

void windowtabwidget::setId(int i){id = i;}

int windowtabwidget::getId(){ return id;}







