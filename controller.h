#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QList>
#include "window.h"
#include "additem.h"
#include "codex.h"
#include "Classes/collection.h"
#include "Classes/tc.cpp"
#include "Classes/tdeep.cpp"
#include "Classes/object.h"

class Controller : public QObject
{
    Q_OBJECT

private:

    Window* window;
    Collection* col;

public:
    explicit Controller(QObject *parent = nullptr);
    void setWindow(Window* w);
    void setCollection(Collection* c);
signals:

public slots:
    void calc() const;
    void getBoxItems();
    void createWeapon();
    void createArmor();
    void createConsumable();
    void showCodex();
    void importChar();
};

#endif // CONTROLLER_H
