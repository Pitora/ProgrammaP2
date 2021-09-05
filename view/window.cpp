#include "window.h"
#include "controller/controller.h"
#include <string>
#include<iostream>

//aggiunge la barra dei menu  e setta i comandi relativi
void Window::addMenu(QHBoxLayout *layout){

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

void Window::addCommand(QHBoxLayout *main)
{
    tab = new QTabWidget();
    QWidget* menu = new QWidget();
    tab->addTab(menu,"Menu");
    tab->setTabsClosable(true);
    tab->tabBar()->tabButton(0,QTabBar::RightSide)->setVisible(false);
    main->addWidget(tab);

    QHBoxLayout* menuL = new QHBoxLayout(menu);
    characters = new QListWidget(this);
    characters->setMinimumSize(200,500);
    characters->setMaximumWidth(350);
    characters->setFont(QFont("Ubuntu",15));
    menuL->addWidget(characters);

    QVBoxLayout* layoutR = new QVBoxLayout();
    menuL->addLayout(layoutR);
    QHBoxLayout* layoutCompare = new QHBoxLayout();
    layoutR->addLayout(layoutCompare);
    compareBox1 = new QTextEdit();
    compareBox2 = new QTextEdit();

    compareBox1->setReadOnly(true);
    compareBox1->setMinimumSize(300,420);
    compareBox1->setFontPointSize(15);

    compareBox2->setReadOnly(true);
    compareBox2->setMinimumSize(300,420);
    compareBox2->setFontPointSize(15);

    layoutCompare->addWidget(compareBox1);
    layoutCompare->addWidget(compareBox2);
    layoutCompare->setAlignment(compareBox1,Qt::AlignTop);
    layoutCompare->setAlignment(compareBox2,Qt::AlignTop);

    QHBoxLayout* layoutButton = new QHBoxLayout();
    layoutR->addLayout(layoutButton);

    import = new QPushButton("Import Build");
    exp = new QPushButton("Export Build");
    def = new QPushButton("Default Build");
    del = new QPushButton("Delete Build");

    import->setMaximumWidth(300);
    exp->setMaximumWidth(300);
    del->setMaximumWidth(300);
    def->setMaximumWidth(300);

    layoutButton->addWidget(import);
    layoutButton->addWidget(exp);
    layoutButton->addWidget(del);
    layoutButton->addWidget(def);


}

void Window::refresh()
{
    characters->clear();
    characters->addItems(controller->getCharNames());
}

//setta la view
Window::Window(QWidget *parent) : QWidget(parent){

    setWindowTitle("Build Creator");
    QHBoxLayout* main = new QHBoxLayout;
    addMenu(main);
    addCommand(main);
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
    connect(characters,SIGNAL(itemClicked(QListWidgetItem*)),controller,SLOT(getInfoChar(QListWidgetItem*)));

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

void Window::refreshCompare(QString c1, QString c2, QString op)
{
    compareBox1->setText(c1);
}

void Window::removeTab(int index)
{
    if(index != 0){
        controller->deleteTab(index);
        tab->removeTab(index);
    }
}

void Window::addTab(QListWidgetItem *i)
{
    int j = characters->currentRow();
    if (!controller->isTabOpen(j))
    {
        windowtabwidget* newTab = new windowtabwidget();
        newTab->setId(j);
        newTab->setController(controller);
        controller->addTab(newTab);
        tab->addTab(newTab,i->text());
    }
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
