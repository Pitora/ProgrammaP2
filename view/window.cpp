#include "window.h"
#include "controller/controller.h"
#include <string>
#include<iostream>

//aggiunge la barra dei menu  e setta i comandi relativi
void Window::addMenu(QHBoxLayout *layout){
    QMenuBar* menu_bar = new QMenuBar(this);

    menu_bar->setStyleSheet("selection-background-color : grey");

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
    QVBoxLayout* buildLayout = new QVBoxLayout();
    menuL->addLayout(buildLayout);

    QLabel* build = new QLabel("BUILD LIST");
    build->setFont(QFont("Ubuntu",15));
    buildLayout->addWidget(build);

    characters = new QListWidget(this);
    characters->setMinimumSize(200,500);
    characters->setMaximumWidth(350);
    characters->setFont(QFont("Ubuntu",17));
    buildLayout->addWidget(characters);
    characters->setStyleSheet(" background-color : rgb(241,217,156)");
    //characters->setAttribute(Qt::WA_NoSystemBackground);

    QVBoxLayout* layoutR = new QVBoxLayout();
    menuL->addLayout(layoutR);

    QHBoxLayout* compL = new QHBoxLayout();
    layoutR->addLayout(compL);

    QLabel* c1 = new QLabel("Build 1");
    c1->setFont(QFont("Ubuntu",15));
    QLabel* c2 = new QLabel("Build 2");
    c2->setFont(QFont("Ubuntu",15));

    compL->addWidget(c1);
    compL->addWidget(c2);

    QHBoxLayout* layoutCompare = new QHBoxLayout();
    layoutR->addLayout(layoutCompare);
    compareBox1 = new QTextEdit();
    compareBox2 = new QTextEdit();

    compareBox1->setReadOnly(true);
    compareBox1->setMinimumSize(300,420);
    compareBox1->setFontPointSize(19);
    compareBox1->setStyleSheet(" background-color : rgb(241,217,156)");

    compareBox2->setReadOnly(true);
    compareBox2->setMinimumSize(300,420);
    compareBox2->setFontPointSize(19);
    compareBox2->setStyleSheet(" background-color : rgb(241,217,156)");

    layoutCompare->addWidget(compareBox1);
    layoutCompare->addWidget(compareBox2);

    QHBoxLayout* comboLayout = new QHBoxLayout();
    layoutR->addLayout(comboLayout);
    comp = new QCheckBox();
    comboLayout->addWidget(comp);
    comboLayout->setAlignment(comp,Qt::AlignHCenter);
    comp->setText("COMPARE");
    comp->setMinimumSize(100,80);
    comp->setMaximumHeight(400);
    comp->setFont(QFont("Ubuntu",15));

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
    //import->setStyleSheet("QPushButton{background-color: rgba(255,255,255,0)}");
    //import->setFlat(true);
    import->setObjectName("import");
    layoutButton->addWidget(exp);
    layoutButton->addWidget(del);
    layoutButton->addWidget(def);

    connect(comp,SIGNAL(clicked(bool)),this,SLOT(lockCompare(bool)));

}

void Window::refresh()
{
    characters->clear();
    comp->setCheckState(Qt::Unchecked);
    compareBox1->clear();
    compareBox2->clear();
    characters->addItems(controller->getCharNames());
}

//setta la view
Window::Window(QWidget *parent) : QWidget(parent){

    setWindowTitle("Build Creator");
    this->setObjectName("window");
    QHBoxLayout* main = new QHBoxLayout;
    addMenu(main);
    addCommand(main);
    setLayout(main);
    this->setStyleSheet(" background-color : rgb(245,210,113)");
    setMinimumSize(1208,700);

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

void Window::showMessage(QString wrn)
{
    QMessageBox* warning = new QMessageBox();
    warning->setText(wrn);
    warning->setIcon(QMessageBox::Warning);
    warning->exec();
}

int Window::getIndSelChar()
{
    return characters->currentRow();
}

bool Window::getCheckValue()
{
    return comp->isChecked();
}

void Window::refreshCompare(QList<QString> list)
{
    if(!comp->isChecked()){
        compareBox1->clear();
        compareBox1->append("Name : " + list[0]+"\n\n");
        for(int i = 1; i< list.length(); i++){
            compareBox1->append(list[i]+"\n");
        }
    }else{
        compareBox2->clear();
        for(int i = 0; i< list.length(); i++){
            compareBox2->append(list[i]);
        }
    }
}

void Window::clearCompare()
{
    compareBox2->clear();
}

void Window::setWithColor(QString s, QColor color)
{
    compareBox2->setTextColor(color);
    compareBox2->append(s);
    compareBox2->setTextColor(Qt::black);
}

void Window::setTabName(QString s)
{
    tab->setTabText(tab->currentIndex(),s);
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

void Window::lockCompare(bool clicked)
{
    if(!clicked){
        compareBox2->clear();
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
