#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QList>
#include <QListWidget>
#include "view/window.h"
#include "view/additem.h"
#include "view/codex.h"
#include "view/windowtabwidget.h"
#include "model/collection.h"
#include "model/tc.cpp"
#include "model/tdeep.cpp"
#include "model/object.h"

class AddItem;
class Codex;

class Controller : public QObject
{
    Q_OBJECT

private:

    Window* window;
    Collection* col;
    Codex* codex;
    AddItem* add;
    QList<int> prevId;
    QList<windowtabwidget*> tabs;
    int activeTab;
    int activeChar;

public:
    explicit Controller(QObject *parent = nullptr);
    void setWindow(Window* w);
    void setCollection(Collection* c);
    void setCodex(Codex* co);
    void setAddItem(AddItem *a);
    void refreshTab();
    void refreshWindow();

    QList<QString> getItemsNames(std::string type, std::string type2);
    QList<int> getItemsId(std::string type, std::string type2);

    QList<QString> getCharNames();

    QColor colorCompare(char c);


signals:

public slots:
    void calc();
    void getBoxItems();
    void createWeaponDialog();
    void createArmorDialog();
    void createConsumableDialog();
    void createMelee(QString n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, QString a_t, QString a_e, int d);
    void createRanged(QString n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, int rec, int rel, int m);
    void createArmor(QString n, QString a_t, QString r, int d_v, int d);
    void createHealing(QString n, QString a_v, int p);
    void createBuff(QString n, QString e, int p, int d);
    void eliminateObj();

    void setWindowChar();
    void setVitality(QString x);
    void setStrenght(QString x);
    void setDexterity(QString x);
    void setAim(QString x);
    void changeName(QString s);
    void changeWeapon(QVariant id);
    void changeArmor(QVariant id);
    void changeItem1(QVariant id);
    void changeItem2(QVariant id);
    void changeItem3(QVariant id);
    void maxAtt();
    void maxDef();

    void addTab(windowtabwidget* t);
    void deleteTab(int index);
    void changeTab(int i);
    bool isTabOpen(int index);

    void optimize();
    void getInfoChar(QListWidgetItem* i);

    void getInfoObj(QListWidgetItem *item);

    void showCodex();

    void importChar();
    void importObj();
    void exportChar();
    void exportObj();

    void sortCodex(QVariant i);

    void defaultChar();
    void deleteChar();
    //void infoChar();
    //void compareChar();

};

#endif // CONTROLLER_H
