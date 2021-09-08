#include "smartcombobox.h"

//variante dell'evento activated
void SmartComboBox::triggerVariantActivated(int index)
{
    activated(itemData(index));
}

SmartComboBox::SmartComboBox(QWidget *parent) : QComboBox(parent)
{
connect(this,SIGNAL(activated(int)),this,SLOT(triggerVariantActivated(int)));
}
