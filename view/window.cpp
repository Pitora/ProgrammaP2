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

void Window::refresh()
{
    characters->clear();
    characters->addItems(controller->getCharNames());
}
/*
//aggiunge e setta le combobox
void Window::addCommand(QVBoxLayout *layout){
}

//aggiunge e setta le label e le textbox
void Window::addLabel(QHBoxLayout* layout){

}

//aggiunge e setta i bottoni
void Window::addButton(QVBoxLayout *layout){
}
*/
//setta la view
Window::Window(QWidget *parent) : QWidget(parent){

    setWindowTitle("Build Creator");
    QVBoxLayout* main = new QVBoxLayout;
    addMenu(main);

    //-------------------------//
    tab = new QTabWidget();
    QWidget* menu = new QWidget();
    QHBoxLayout* menuL = new QHBoxLayout();
    QVBoxLayout* menuB = new QVBoxLayout();
    menu->setLayout(menuL);
    tab->addTab(menu,"Menu");
    tab->setTabsClosable(true);
    tab->tabBar()->tabButton(0,QTabBar::RightSide)->setVisible(false);
    main->addWidget(tab);

    characters = new QListWidget();
    menuL->addWidget(characters);
    menuL->addLayout(menuB);
    import = new QPushButton("Import Build");
    exp = new QPushButton("Export Build");
    def = new QPushButton("Default Build");
    del = new QPushButton("Delete Build");

    import->setMaximumWidth(300);
    exp->setMaximumWidth(300);
    del->setMaximumWidth(300);
    def->setMaximumWidth(300);
    menuB->addWidget(import);
    menuB->addWidget(exp);
    menuB->addWidget(def);
    menuB->addWidget(del);
    //-------------------------//


    /*addCommand(main);
    addButton(main);*/
    setLayout(main);
    setMinimumSize(1024,600);

}

//setta il controller
void Window::setController(Controller *c){
    controller = c;

    connect(file->actions()[0],SIGNAL(triggered()),this,SLOT(close()));
    connect(create->actions()[0],SIGNAL(triggered()),controller,SLOT(createWeaponDialog()));
    connect(create->actions()[1],SIGNAL(triggered()),controller,SLOT(createArmorDialog()));
    connect(create->actions()[2],SIGNAL(triggered()),controller,SLOT(createConsumableDialog()));
    connect(create->actions()[3],SIGNAL(triggered()),controller,SLOT(showCodex()));

    connect(characters,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(addTab(QListWidgetItem*)));
    connect(tab,SIGNAL(currentChanged(int)),controller,SLOT(changeTab(int)));
    connect(tab,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));

    connect(import,SIGNAL(clicked(bool)),controller,SLOT(importChar()));
    connect(exp,SIGNAL(clicked(bool)),controller,SLOT(exportChar()));
    connect(del,SIGNAL(clicked(bool)),controller,SLOT(deleteChar()));
    connect(def,SIGNAL(clicked(bool)),controller,SLOT(defaultChar()));

    controller->refreshWindow();

}

int Window::getIndSelChar()
{
 return characters->currentRow();
}
/*
//imposta l'attacco e la difesa
void Window::calcDmgDef(int a,int d){
}

//carica le combobox
void Window::loadBox(QList<QString> n, QList<int> id,int i)
{
}

//imposta il nome della build caricata
void Window::setBuildName(QString s)
{
}

//imposta le stat della build caricata
void Window::setStats(QList<QString> l)
{
}

//imposta l'arma della build caricata
void Window::setWeapon(int s)
{
}

//imposta i pezzi di equipaggiamento della build quando caricata
void Window::setArmor(QList<int> l)
{
}

//imposta gli oggetti della build quando caricata
void Window::setItems(QList<int> l)
{
}*/

void Window::addTab(QListWidgetItem *i)
{
    windowtabwidget* newTab = new windowtabwidget();
    int j = characters->currentRow();
    newTab->setId(j);
    newTab->setController(controller);
    controller->addTab(newTab);
    tab->addTab(newTab,i->text());
}

void Window::closeTab(int index)
{
    if(index != 0){
        controller->deleteTab(index);
        delete tab->widget(index);
    }
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
