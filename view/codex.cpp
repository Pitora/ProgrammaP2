#include "codex.h"

//setta la view
Codex::Codex(Controller *c,QList<QString> list,QList<int> id, QWidget *parent) : QDialog(parent)
{
    controller = c;

    setWindowTitle("Codex");
    setMinimumSize(500,600);
    setStyleSheet("background-color : rgb(49, 163, 112)");
    setCursor(QCursor(QPixmap("assets/cursor.png"),0,0));

    QHBoxLayout* main = new QHBoxLayout();
    setLayout(main);

    addCommands(main);
    setCommands(list,id);

}

//aggiunge e crea lista, combobox e box dettagli
void Codex::addCommands(QHBoxLayout *layout)
{
    QVBoxLayout* listLayout = new QVBoxLayout(); //crea il layout con combobox e lista
    layout->addLayout(listLayout);

    /* crea e setta la combobox */
    sort_item = new SmartComboBox(this);
    sort_item->setStyleSheet("QComboBox{selection-background-color : grey}");
    sort_item->setFont(QFont("Ubuntu",15));

    /* crea e setta la lista */
    cont = new QListWidget();
    cont->setFont(QFont("Ubuntu",15));
    cont->setStyleSheet("QListWidget{background-color : rgb(62, 207, 142)}");

    /* aggiunge lista e combobox al layout */
    listLayout->addWidget(sort_item);
    listLayout->addWidget(cont);

    /*  crea il layout con box dettagli e bottoni */
    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins(0,32,0,0);
    rightLayout->setSpacing(20);

    layout->addLayout(rightLayout);

    /* crea e setta la box dettagli */
    details = new QTextEdit();
    details->setFontPointSize(20);
    details->setReadOnly(true);
    details->setFrameShape(QFrame::NoFrame);
    details->setAttribute(Qt::WA_NoSystemBackground);

    rightLayout->addWidget(details);

    addControls(rightLayout);

}

//setta la scroll area e la combobox
void Codex::setCommands(QList<QString> l,QList<int> id)
{

    cont->clear();

    sort_item->addItem("All",QVariant(0));
    sort_item->addItem("<Weapon>",QVariant(1));
    sort_item->addItem("__Melee",QVariant(2));
    sort_item->addItem("__Ranged",QVariant(3));
    sort_item->addItem("<Armor>",QVariant(4));
    sort_item->addItem("__Helm",QVariant(5));
    sort_item->addItem("__Chest",QVariant(7));
    sort_item->addItem("__Gloves",QVariant(8));
    sort_item->addItem("__Boots",QVariant(9));
    sort_item->addItem("<Consumable>",QVariant(10));
    sort_item->addItem("__Buff",QVariant(11));
    sort_item->addItem("__Healing",QVariant(12));

    for(int i = 0; i < l.size();i++){
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(l[i]);
        item->setData(Qt::UserRole,id[i]);
        cont->addItem(item);
    }

    connect(cont,SIGNAL(itemClicked(QListWidgetItem*)),controller,SLOT(getInfoObj(QListWidgetItem*)));
    connect(sort_item,SIGNAL(activated(QVariant)),controller,SLOT(sortCodex(QVariant)));
}

//setta e aggiunge i bottoni
void Codex::addControls(QVBoxLayout* layout)
{

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    layout->addLayout(buttonsLayout);
    remove_item = new QPushButton("Remove",this);
    import_item = new QPushButton("Import",this);
    export_item = new QPushButton("Export",this);

    buttonsLayout->addWidget(remove_item);
    buttonsLayout->addWidget(import_item);
    buttonsLayout->addWidget(export_item);

    remove_item->setEnabled(false);
    export_item->setEnabled(false);

    connect(remove_item,SIGNAL(clicked()),controller,SLOT(eliminateObj()));
    connect(import_item,SIGNAL(clicked()),controller,SLOT(importObj()));
    connect(export_item,SIGNAL(clicked()),controller,SLOT(exportObj()));

}

//refresha la view
void Codex::refreshCodex(QList<QString> l,QList<int> id)
{
    remove_item->setEnabled(false);
    export_item->setEnabled(false);
    cont->clear();
    for(int i = 0; i < l.size();i++){
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(l[i]);
        item->setData(Qt::UserRole,id[i]);
        cont->addItem(item);
    }
    details->clear();
    controller->refreshTab();
}

//ritorna l'oggetto selezionato
QListWidgetItem* Codex::getSelectedItem()
{
    return cont->currentItem();
}

int Codex::getSortInd(){return sort_item->currentIndex();}

//mostra il dialog per l'esportazione
QString Codex::showExpDialog()
{
    QString fileName = QFileDialog::getSaveFileName(
                this, tr("Export File"), "/home", tr("XML File (*.xml)"));
        if (fileName == "")
            throw std::runtime_error("No File Selected");
        return fileName;
}

//mostra il dialog per l'importazione
QString Codex::showImportDialog()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Import File"), "/home", tr("XML File (*.xml)"));
        if (fileName == "")
            throw std::runtime_error("No File Selected");
        return fileName;
}

//imposta i dettagli dell'oggetto
void Codex::showDetails(QString s)
{
    remove_item->setEnabled(true);
    export_item->setEnabled(true);
    details->setText(s);
}
