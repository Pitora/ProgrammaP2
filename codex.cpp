#include "codex.h"

Codex::Codex(Controller *cont, QWidget *parent) : QDialog(parent)
{
    c = cont;
    setWindowTitle("Codex");
    setFixedSize(500,600);
    addScrollArea();
    addControls();

}

void Codex::addScrollArea()
{
    cont = new QListWidget(this);
    cont->setGeometry(20,20,200,550);
    cont->setFrameShape(QFrame::NoFrame);
    QPalette pal = cont->palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window));
    cont->setPalette(pal);

    for(int i = 0; i < 100; i++){
         cont->addItem(QString::number(i));
     }

    connect(cont,SIGNAL(itemClicked(QListWidgetItem*)),c,SLOT(getInfoObj(QListWidgetItem*)));

    details = new QTextEdit(this);
    details->setGeometry(250,20,220,500);
    details->setReadOnly(true);
    details->setPalette(pal);

    details->setReadOnly(true);
    details->setFrameShape(QFrame::NoFrame);

}

void Codex::addControls()
{
    remove_item = new QPushButton("Remove",this);
    import_item = new QPushButton("Import",this);
    export_item = new QPushButton("Export",this);

    remove_item->setGeometry(240,520,60,30);
    import_item->setGeometry(310,520,60,30);
    export_item->setGeometry(380,520,60,30);

    connect(remove_item,SIGNAL(clicked()),c,SLOT(eliminateObj(int)));
    connect(import_item,SIGNAL(clicked()),c,SLOT(importObj()));
    connect(export_item,SIGNAL(clicked()),c,SLOT(exportObj()));

}

void Codex::showDetails(QString s)
{
    details->setText(s);
}
