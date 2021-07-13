#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QList>
#include <QListWidget>
#include "window.h"
#include "additem.h"
#include "codex.h"
#include "Classes/collection.h"
#include "Classes/tc.cpp"
#include "Classes/tdeep.cpp"
#include "Classes/object.h"

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
    int prevId;

public:
    explicit Controller(QObject *parent = nullptr);
    void setWindow(Window* w);
    void setCollection(Collection* c);
    void setCodex(Codex* co);
    void setAddItem(AddItem *a);

    QList<QString> getItemsNames();
signals:

public slots:
    void calc() const;
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
    void changeWeapon(QString s);
    void changeArmor(int id1, int id2);
    void changeItem(int id1, int id2);

    void getInfoObj(QListWidgetItem *item);

    void getPrevId(QString s);

    void showCodex();

    void importChar();
    void importObj();
    void exportChar();
    void exportObj();
};

#endif // CONTROLLER_H
