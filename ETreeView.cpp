#include "ETreeView.h"

ETreeView::ETreeView(int treeRowIndex = 1) :
    m_layout    (new QGridLayout),
    m_tree      (new QTreeView)
{
    if (treeRowIndex < 0)
    {
        treeRowIndex = 0;
        //Warning message ?
    }

    //Set appearance
    m_tree->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
    m_tree->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
    setStyleSheet("QTreeView { alternate-background-color: yellow }");
    m_tree->header()->hide();

    //Place the tree
    m_layout->addWidget(m_tree, treeRowIndex, 0);
    setLayout(m_layout);
}

void ETreeView::addWidget(QWidget * widget, int row, int column, int rowSpan, int columnSpan, Qt::Alignment alignment)
{
    m_layout->addWidget(widget, row, column, rowSpan, columnSpan, alignment);
}
