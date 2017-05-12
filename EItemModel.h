#ifndef EITEMMODEL_H
#define EITEMMODEL_H

#include <QStandardItemModel>
#include <QVector>
#include <vector>
#include "EItem.h"

class EItemModel : public QStandardItemModel
{
private :
    //A map which links EItems to QString in order to access those in a readable way.
    QVector<QPersistentModelIndex*> m_titles;

public:
    EItemModel();
    ~EItemModel();

    //Add a title into the model
    //Titles are the only items which are meant to have no parent item
    //They're not corresponding to any object, so they're not even selectable
    void addTitle(const QString & text);
    void addTitle(const QVector<QString> & texts);

    //To access a title

    int getNbTitles() const {return m_titles.size();}

    //If there is no such title, returns null pointer
    QStandardItem* getTitle(int index);

    //Change the name of a title; no consequences on child items.
    void changeTitle(int index, const QString &text);
};

#endif // EITEMMODEL_H
