#include "codex.h"

Codex::Codex(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Codex");
    setFixedSize(500,600);
    addScrollArea();

}

void Codex::addScrollArea()
{
    container = new QScrollArea(this);
    container->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    container->setWidgetResizable(true);
    container->setGeometry(20,20,200,550);
    container->setFrameShape(QFrame::NoFrame);

    QWidget* widget = new QWidget();
    container->setWidget(widget);

    QVBoxLayout* layout = new QVBoxLayout();
    widget->setLayout(layout);

    for(int i = 0; i < 50; i++){
        QPushButton* item = new QPushButton(QString::number(i));
        item->setFlat(true);
        item->setFixedSize(160,30);
        layout->addWidget(item);
        connect(item,SIGNAL(clicked()),this,SLOT(showDetails()));
    }

    details = new QTextEdit(this);
    details->setGeometry(250,20,220,550);
    details->setReadOnly(true);
    details->setText("ASDASDASDASDASDASDASDAS\n asdadsasdads\nasdasdasdasdasdsasd");

    QPalette pal = details->palette();
    pal.setColor(QPalette::Base,pal.color(QPalette::Window));
    details->setPalette(pal);

    details->setReadOnly(true);
    details->setFrameShape(QFrame::NoFrame);



}

void Codex::showDetails()
{
    details->setText("bravo\nsamu\nperò\nvilla\nè\ngay\n");
}
