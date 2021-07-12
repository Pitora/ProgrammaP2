#include "window.h"
#include "controller.h"
#include <string>
#include<iostream>

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

void Window::addCommand(QVBoxLayout *layout){

    QHBoxLayout* hLayout = new QHBoxLayout;
   // QVBoxLayout* infoLayout = new QVBoxLayout;
    QFormLayout* form = new QFormLayout;

    layout->addLayout(hLayout);
    hLayout->addLayout(form);
   // hLayout->addLayout(infoLayout);

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


    weapon_box->setMaximumWidth(250);
    helm_box->setMaximumWidth(250);
    chest_box->setMaximumWidth(250);
    gloves_box->setMaximumWidth(250);
    boots_box->setMaximumWidth(250);
    item1_box->setMaximumWidth(250);
    item2_box->setMaximumWidth(250);
    item3_box->setMaximumWidth(250);

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

void Window::addLabel(QHBoxLayout* layout){

    QFormLayout* midLayout = new QFormLayout;
    QFormLayout* rightLayout = new QFormLayout;

    midLayout->setContentsMargins(11,20,0,0);
    layout->addLayout(midLayout);
    layout->addLayout(rightLayout);
    midLayout->setSpacing(30);

    stats_lbl = new QLabel();
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

    stats_lbl->setText("MAX POWER");
    atk_lbl->setText("ATK : 500");
    def_lbl->setText("DEF : 500");

    vit_text->setMaximumWidth(70);
    str_text->setMaximumWidth(70);
    dex_text->setMaximumWidth(70);
    aim_text->setMaximumWidth(70);

    vit_text->setText("500");
    str_text->setText("400");
    dex_text->setText("300");
    aim_text->setText("400");

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

    midLayout->addWidget(stats_lbl);
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

void Window::addButton(QVBoxLayout *layout){

    QHBoxLayout* hLayout = new QHBoxLayout;
    layout->addLayout(hLayout);

    calculate = new QPushButton("Calculate");
    import = new QPushButton("Import");
    save = new QPushButton("Save");

    hLayout->addWidget(calculate);
    hLayout->addWidget(import);
    hLayout->addWidget(save);
}

Window::Window(QWidget *parent) : QWidget(parent){

    setWindowTitle("Build Creator");
    QVBoxLayout* main = new QVBoxLayout;
    addMenu(main);
    addCommand(main);
    addButton(main);
    setLayout(main);
    setFixedSize(900,600);

}

void Window::setController(Controller *c){
    controller = c;

    connect(save,SIGNAL(clicked()),controller,SLOT(close()));
    connect(import,SIGNAL(clicked()),controller,SLOT(importChar()));
    connect(calculate,SIGNAL(clicked()),controller,SLOT(calc()));

    connect(create->actions()[0],SIGNAL(triggered()),controller,SLOT(createWeaponDialog()));
    connect(create->actions()[1],SIGNAL(triggered()),controller,SLOT(createArmorDialog()));
    connect(create->actions()[2],SIGNAL(triggered()),controller,SLOT(createConsumableDialog()));
    connect(create->actions()[3],SIGNAL(triggered()),controller,SLOT(showCodex()));

}

void Window::calcDmgDef(){
    atk_lbl->setText("ATK : " );
    def_lbl->setText("DEF : " );
}

void Window::loadBox(QList<QString> n,int i)
{
    switch (i) {
    case 1:
        weapon_box->addItems(n);
        break;
    case 2:
        helm_box->addItems(n);
        break;
    case 3:
        chest_box->addItems(n);
        break;
    case 4:
        gloves_box->addItems(n);
        break;
    case 5:
        boots_box->addItems(n);
        break;
    case 6:
        item1_box->addItems(n);
        item2_box->addItems(n);
        item3_box->addItems(n);
        break;
    default:
        break;
    }
}

QString Window::importFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(
            this, tr("Open File"), "/home", tr("XML File (*.xml)"));
    if (fileName == "")
        throw std::runtime_error("No File Selected");
    return fileName;
}

Window::~Window()
{
}
