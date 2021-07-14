#include "window.h"
#include "controller/controller.h"
#include <string>
#include<iostream>

//aggiunge la barra dei menu  e setta i comandi relativi
void Window::addMenu(QVBoxLayout *layout){

    QMenuBar* menu_bar = new QMenuBar(this);

    file = new QMenu("File",menu_bar);
    create = new QMenu("Options",menu_bar);
    menu_bar->addMenu(file);
    menu_bar->addMenu(create);
    create->addAction(new QAction("Create Weapon",file));
    create->addAction(new QAction("Create Armor Piece",file));
    create->addAction(new QAction("Create Consumable",file));
    create->addAction(new QAction("Codex",file));
    file->addAction(new QAction("Quit",file));
    layout->setMenuBar(menu_bar);
}

//aggiunge e setta le combobox
void Window::addCommand(QVBoxLayout *layout){

    QHBoxLayout* hLayout = new QHBoxLayout;
    QFormLayout* form = new QFormLayout;

    layout->addLayout(hLayout);
    hLayout->addLayout(form);

    form->setRowWrapPolicy(QFormLayout::WrapAllRows);
    form->setVerticalSpacing(10);
    form->setContentsMargins(11,20,0,0);

    weapon_box = new QComboBox();
    helm_box = new QComboBox();
    chest_box = new QComboBox();
    gloves_box = new QComboBox();
    boots_box = new QComboBox();
    item1_box = new QComboBox();
    item2_box = new QComboBox();
    item3_box = new QComboBox();

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

//aggiunge e setta le label e le textbox
void Window::addLabel(QHBoxLayout* layout){

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

//aggiunge e setta i bottoni
void Window::addButton(QVBoxLayout *layout){

    QHBoxLayout* hLayout = new QHBoxLayout;
    layout->addLayout(hLayout);

    import = new QPushButton("Import Build");
    save = new QPushButton("Export Build");

    import->setMaximumWidth(300);
    save->setMaximumWidth(300);

    hLayout->addWidget(import);
    hLayout->addWidget(save);
}

//setta la view
Window::Window(QWidget *parent) : QWidget(parent){

    setWindowTitle("Build Creator");
    QVBoxLayout* main = new QVBoxLayout;
    addMenu(main);
    addCommand(main);
    addButton(main);
    setLayout(main);
    setFixedSize(1024,600);

}

//setta il controller
void Window::setController(Controller *c){
    controller = c;

    connect(save,SIGNAL(clicked()),controller,SLOT(exportChar()));
    connect(import,SIGNAL(clicked()),controller,SLOT(importChar()));

    connect(file->actions()[0],SIGNAL(triggered()),this,SLOT(close()));
    connect(create->actions()[0],SIGNAL(triggered()),controller,SLOT(createWeaponDialog()));
    connect(create->actions()[1],SIGNAL(triggered()),controller,SLOT(createArmorDialog()));
    connect(create->actions()[2],SIGNAL(triggered()),controller,SLOT(createConsumableDialog()));
    connect(create->actions()[3],SIGNAL(triggered()),controller,SLOT(showCodex()));

    connect(vit_text,SIGNAL(textChanged(QString)),controller,SLOT(setVitality(QString)));
    connect(str_text,SIGNAL(textChanged(QString)),controller,SLOT(setStrenght(QString)));
    connect(dex_text,SIGNAL(textChanged(QString)),controller,SLOT(setDexterity(QString)));
    connect(aim_text,SIGNAL(textChanged(QString)),controller,SLOT(setAim(QString)));

    connect(build_name,SIGNAL(textChanged(QString)),controller,SLOT(changeName(QString)));

    connect(weapon_box,SIGNAL(activated(QString)),controller,SLOT(changeWeapon(QString)));
    connect(helm_box,SIGNAL(activated(QString)),controller,SLOT(changeArmor(QString)));
    connect(chest_box,SIGNAL(activated(QString)),controller,SLOT(changeArmor(QString)));
    connect(gloves_box,SIGNAL(activated(QString)),controller,SLOT(changeArmor(QString)));
    connect(boots_box,SIGNAL(activated(QString)),controller,SLOT(changeArmor(QString)));
    connect(item1_box,SIGNAL(activated(QString)),controller,SLOT(changeItem1(QString)));
    connect(item2_box,SIGNAL(activated(QString)),controller,SLOT(changeItem2(QString)));
    connect(item3_box,SIGNAL(activated(QString)),controller,SLOT(changeItem3(QString)));

}

//imposta l'attacco e la difesa
void Window::calcDmgDef(int a,int d){
    atk_lbl->setText("ATK : " + QString::number(a) );
    def_lbl->setText("DEF : " + QString::number(d));
}

//carica le combobox
void Window::loadBox(QList<QString> n,int i)
{
    switch (i) {
    case 1:
        weapon_box->clear();
        weapon_box->addItems(n);
        break;
    case 2:
        helm_box->clear();
        helm_box->addItems(n);
        break;
    case 3:
        chest_box->clear();
        chest_box->addItems(n);
        break;
    case 4:
        gloves_box->clear();
        gloves_box->addItems(n);
        break;
    case 5:
        boots_box->clear();
        boots_box->addItems(n);
        break;
    case 6:
        item1_box->clear();
        item2_box->clear();
        item3_box->clear();
        item1_box->addItems(n);
        item2_box->addItems(n);
        item3_box->addItems(n);
        break;
    default:
        break;
    }
}

//imposta il nome della build caricata
void Window::setBuildName(QString s)
{
    build_name->setText(s);
}

//imposta le stat della build caricata
void Window::setStats(QList<QString> l)
{
    vit_text->setText(l[0]);
    str_text->setText(l[1]);
    dex_text->setText(l[2]);
    aim_text->setText(l[3]);
}

//imposta l'arma della build caricata
void Window::setWeapon(QString s)
{
    weapon_box->setCurrentIndex(weapon_box->findText(s));
}

//imposta i pezzi di equipaggiamento della build quando caricata
void Window::setArmor(QList<QString> l)
{
    for(auto i = l.begin(); i != l.end(); ++i){
        if(helm_box->findText(*i) != -1){
            helm_box->setCurrentIndex(helm_box->findText(*i));
        }
        if(chest_box->findText(*i) != -1){
            chest_box->setCurrentIndex(chest_box->findText(*i));
        }
        if(gloves_box->findText(*i) != -1){
            gloves_box->setCurrentIndex(gloves_box->findText(*i));
        }
        if(boots_box->findText(*i) != -1){
            boots_box->setCurrentIndex(boots_box->findText(*i));
        }
    }
}

//imposta gli oggetti della build quando caricata
void Window::setItems(QList<QString> l)
{
    item1_box->setCurrentIndex(item1_box->findText(l[0]));
    item2_box->setCurrentIndex(item2_box->findText(l[1]));
    item3_box->setCurrentIndex(item3_box->findText(l[2]));
}

//finestra di dialogo per l'import di una build
QString Window::importCharDialog()
{
    QString fileName = QFileDialog::getOpenFileName(
            this, tr("Import character"), "/home", tr("XML File (*.xml)"));
    if (fileName == "")
        throw std::runtime_error("No File Selected");
    return fileName;
}

//finestra di dialogo per l'export di una build
QString Window::exportCharDialog()
{
    QString fileName = QFileDialog::getSaveFileName(
            this, tr("Export character"), "/home", tr("XML File (*.xml)"));
    if (fileName == "")
        throw std::runtime_error("No name");
    return fileName;
}

Window::~Window()
{
}
