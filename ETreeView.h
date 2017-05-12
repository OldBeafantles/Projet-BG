#ifndef ETREEVIEW_H
#define ETREEVIEW_H

#include <QTreeView>
#include <QStandardItemModel>
#include <QGridLayout>
#include <QScrollBar>
#include <QHeaderView>
#include "EConstants.h"
#include "EItemModel.h"

class ETreeView : public QWidget
{
    Q_OBJECT

private :
    //QGridLayout and not QVBoxLayout because we want to add widgets above and below the tree.
    QGridLayout *m_layout;

protected :
    QTreeView *m_tree;

public :
    //Constructors
    ETreeView(int treeRowIndex);

    //Getter
    QTreeView* getTreeView() const {return m_tree;}

    //Other
    void addWidget(QWidget * widget, int row, int column = 0, int rowSpan = 1, int columnSpan = 1, Qt::Alignment alignment = Qt::Alignment());

signals :
    //This signal should send a GObject pointer.
    void objectSelected(QString *);

};

#endif // ETREEVIEW_H
