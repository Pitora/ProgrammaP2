#include "codex.h"

Codex::Codex(Controller *cont,QList<QString> list, QWidget *parent) : QDialog(parent)
{
    c = cont;
    setWindowTitle("Codex");
    setFixedSize(500,600);

    addScrollArea(list);
    addControls();

}

void Codex::addScrollArea(QList<QString> l)
{
    cont = new QListWidget(this);
    cont->clear();
    cont->setGeometry(20,20,200,550);
    cont->setFrameShape(QFrame::NoFrame);
    QPalette pal = cont->palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window));
    cont->setPalette(pal);
    cont->addItems(l);

    details = new QTextEdit(this);
    details->setGeometry(250,20,220,500);
    details->setReadOnly(true);
    details->setPalette(pal);

    details->setReadOnly(true);
    details->setFrameShape(QFrame::NoFrame);

    connect(cont,SIGNAL(itemClicked(QListWidgetItem*)),c,SLOT(getInfoObj(QListWidgetItem*)));


}

void Codex::addControls()
{
    remove_item = new QPushButton("Remove",this);
    import_item = new QPushButton("Import",this);
    export_item = new QPushButton("Export",this);

    remove_item->setGeometry(240,520,60,30);
    import_item->setGeometry(310,520,60,30);
    export_item->setGeometry(380,520,60,30);

    connect(remove_item,SIGNAL(clicked()),c,SLOT(eliminateObj()));
    connect(import_item,SIGNAL(clicked()),c,SLOT(importObj()));
    connect(export_item,SIGNAL(clicked()),c,SLOT(exportObj()));

}

void Codex::refreshCodex(QList<QString> l)
{
    cont->clear();
    cont->addItems(l);
    details->clear();
}

QString Codex::getSelectedItem()
{
    return cont->currentItem()->text();
}

QString Codex::showExpDialog()
{
    QString fileName = QFileDialog::getSaveFileName(
                this, tr("Export File"), "/home", tr("XML File (*.xml)"));
        if (fileName == "")
            throw std::runtime_error("No File Selected");
        return fileName;
}


QString Codex::showImportDialog()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Import File"), "/home", tr("XML File (*.xml)"));
        if (fileName == "")
            throw std::runtime_error("No File Selected");
        return fileName;
}

void Codex::showDetails(QString s)
{
    details->setText(s);
}
