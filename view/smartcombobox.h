#ifndef SMARTCOMBOBOX_H
#define SMARTCOMBOBOX_H
#include <QComboBox>

class SmartComboBox : public QComboBox
{
    Q_OBJECT

private slots:
    void triggerVariantActivated(int index);
public:
    SmartComboBox(QWidget *parent);

signals:
    void activated(const QVariant &);
};

#endif // SMARTCOMBOBOX_H
