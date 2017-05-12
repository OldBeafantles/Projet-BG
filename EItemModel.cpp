#include "EItemModel.h"

EItemModel::EItemModel() :
    QStandardItemModel(),
    m_titles (QVector<QPersistentModelIndex*>())
{

}

EItemModel::~EItemModel()
{
    for (int i = 0; i < m_titles.size(); i++)
        delete m_titles[i];
}

void EItemModel::addTitle(const QString & text)
{
    //Create the actual title object
    QStandardItem *title = new QStandardItem(text);

    //Make it uneditable and unselectable
    title->setFlags(title->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);

    //Add the title into the model
    appendRow(title);

    //Create a model index and store it directly in the map
    m_titles.append(new QPersistentModelIndex(createIndex(rowCount() - 1, 0)));

}

void EItemModel::addTitle(const QVector<QString> & texts)
{
    for (int i = 0; i < texts.size(); i++)
        addTitle(texts[i]);
}

QStandardItem* EItemModel::getTitle(int index)
{
    //Checks if key is an actual key. Returns null pointer if it's not the case.
    return itemFromIndex((const QModelIndex &) m_titles[index]);
}

void EItemModel::changeTitle(int index, const QString & text)
{
    getTitle(index)->setText(text);
}
