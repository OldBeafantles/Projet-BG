#ifndef EITEM_H
#define EITEM_H

#include <QStandardItem>

class EItem : public QStandardItem
{
private :
    //Here comes a QObject pointer
public :
    EItem();
    //This constructor should take as argument a GObject pointer, null by default

    //There should be a reimplementation of text() and setText() methods, as text should be the name of the pointed QObject
};

#endif // EITEM_H
