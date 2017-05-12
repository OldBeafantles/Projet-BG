#include "EItem.h"

EItem::EItem() :
    QStandardItem()
{
    setFlags(flags() & ~Qt::ItemIsEditable);

    //Only for test purpose
    setText("EItem test");
}
