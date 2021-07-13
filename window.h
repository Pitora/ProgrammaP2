#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QString>
#include <QComboBox>
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpacerItem>
#include <QFileDialog>
#include <utility>

class Controller;

class Window : public QWidget
{
    Q_OBJECT
private:

    QMenu* file;
    QMenu* create;

    QPushButton* import;
    QPushButton* save;

    QComboBox* weapon_box;
    QComboBox* helm_box;
    QComboBox* chest_box;
    QComboBox* gloves_box;
    QComboBox* boots_box;
    QComboBox* item1_box;
    QComboBox* item2_box;
    QComboBox* item3_box;

    QLineEdit* build_name;
    QLabel* atk_lbl;
    QLabel* def_lbl;

    QLabel* vit_lbl;
    QLabel* str_lbl;
    QLabel* dex_lbl;
    QLabel* aim_lbl;

    QLineEdit* vit_text;
    QLineEdit* str_text;
    QLineEdit* dex_text;
    QLineEdit* aim_text;

    Controller* controller;

    void addMenu(QVBoxLayout *layout);
    void addCommand(QVBoxLayout *layout);
    void addLabel(QHBoxLayout* layout);
    void addButton(QVBoxLayout* layout);


public:

    Window(QWidget *parent = 0);
    void setController(Controller *c);
    void calcDmgDef(int a, int d);
    void loadBox(QList<QString> n, int i);
    QString importCharDialog();
    QString exportCharDialog();
    ~Window();

};

#endif // WINDOW_H
