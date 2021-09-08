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

    file->setCursor(QCursor(QPixmap("assets/cursor.png"),0,0));
    create->setCursor(QCursor(QPixmap("assets/cursor.png"),0,0));

    menu_bar->addMenu(file);
    menu_bar->addMenu(create);

    create->addAction(new QAction("Create Weapon",file));
    create->addAction(new QAction("Create Armor Piece",file));
    create->addAction(new QAction("Create Consumable",file));
    create->addAction(new QAction("Codex",file));
    file->addAction(new QAction("Quit",file));

    layout->setMenuBar(menu_bar);
}

//aggiunge il tab widget con la pagina iniziale
void Window::addTab(QHBoxLayout *main)
{
    tab = new QTabWidget();
    QWidget* menu = new QWidget();

    tab->addTab(menu,"Menu");
    tab->setTabsClosable(true);
    tab->tabBar()->tabButton(0,QTabBar::RightSide)->setVisible(false);
    main->addWidget(tab);

    QHBoxLayout* menuL = new QHBoxLayout(menu);
    addList(menuL);

    addCompareCommands(menuL);
}

//aggiunge la listbox e le label sottostanti
void Window::addList(QHBoxLayout *layout)
{
    QVBoxLayout* buildLayout = new QVBoxLayout();
    layout->addLayout(buildLayout);

    QLabel* build = new QLabel("BUILD LIST");
    build->setFont(QFont("Ubuntu",15));
    buildLayout->addWidget(build);

    characters = new QListWidget(this);
    characters->setMinimumSize(200,500);
    characters->setMaximumWidth(350);
    characters->setFont(QFont("Ubuntu",17));
    characters->setStyleSheet(" background-color : rgb(241,217,156)");
    buildLayout->addWidget(characters);

    QLabel* help =new QLabel("Click once to show build preview\nDouble click to modify build");
    help->setFont(QFont("Ubuntu",10,-1,true));
    buildLayout->addWidget(help);
}

//aggiunge le label,le combobox e il checkbox del compare
void Window::addCompareCommands(QHBoxLayout *layout)
{
    QVBoxLayout* layoutR = new QVBoxLayout();       //layout il layout della label build , dei box compare del bottone compare e dei bottoni import,del,def,exp
    layout->addLayout(layoutR);

    QHBoxLayout* compL = new QHBoxLayout();        //layout con le label build 1 e 2
    layoutR->addLayout(compL);

    QLabel* c1 = new QLabel("Build 1");
    QLabel* c2 = new QLabel("Build 2");

    c1->setFont(QFont("Ubuntu",15));
    c2->setFont(QFont("Ubuntu",15));

    compL->addWidget(c1);
    compL->addWidget(c2);

    /*crea e setta il layout con i compare box */

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

    /* creazione layout bottone compare e personalizzazione checkbox*/

    QHBoxLayout* compLayout = new QHBoxLayout();
    layoutR->addLayout(compLayout);

    comp = new QCheckBox();
    compLayout->addWidget(comp);
    compLayout->setAlignment(comp,Qt::AlignHCenter);
    comp->setText("COMPARE");
    comp->setMinimumSize(100,80);
    comp->setMaximumHeight(400);
    comp->setFont(QFont("Ubuntu",15));
    comp->setDisabled(true);
    connect(comp,SIGNAL(clicked(bool)),this,SLOT(lockCompare(bool)));

    addButtons(layoutR);

}

//aggiunge i bottoni import,exp,del e def
void Window::addButtons(QVBoxLayout *layout)
{
    QHBoxLayout* layoutButton = new QHBoxLayout();
    layout->addLayout(layoutButton);

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
    comp->setDisabled(true);
    comp->setCheckState(Qt::Unchecked);
    compareBox1->clear();
    compareBox2->clear();
    characters->addItems(controller->getCharNames());
}

//setta la view
Window::Window(QWidget *parent) : QWidget(parent){

    setWindowTitle("Build Creator");

    QHBoxLayout* main = new QHBoxLayout;
    addMenu(main);
    addTab(main);
    setLayout(main);

    setStyleSheet(" background-color : rgb(245,210,113)");
    setMinimumSize(1300,700);
    setCursor(QCursor(QPixmap("assets/cursor.png"),0,0));

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

//ritorna l'indice della build selezionata
int Window::getIndSelChar()
{
    comp->setDisabled(false);
    return characters->currentRow();
}

//ritorna il valore della checkbox
bool Window::getCheckValue()
{
    return comp->isChecked();
}

//esegue un refresh delle textbox
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

//svuota il comparebox2
void Window::clearCompare()
{
    compareBox2->clear();
}

//aggiunge una riga colorata nella box compare
void Window::setWithColor(QString s, QColor color)
{
    compareBox2->setTextColor(color);
    compareBox2->append(s);
    compareBox2->setTextColor(Qt::black);
}

//cambia nome alla tab
void Window::setTabName(QString s)
{
    tab->setTabText(tab->currentIndex(),s);
}

//apre una tab
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
        tab->tabBar()->tabButton((tab->count()-1),QTabBar::RightSide)->setCursor(this->cursor());
    }
}

//chiude una tab
void Window::closeTab(int index)
{
    if(index != 0){
        controller->deleteTab(index);
        delete tab->widget(index);
    }
}

//blocca la checkbox
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
