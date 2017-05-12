#include "ETabTreeView.h"
#include <QMessageBox>

ETabTreeView::ETabTreeView() :
    ETreeView(1),
    m_tabs          (new QTabBar),
    m_models        (std::vector<EItemModel*>())
{
    QObject::connect(m_tabs, SIGNAL(currentChanged(int)), this, SLOT(setCurrentModel(int)));

    addWidget(m_tabs, 0);
}


ETabTreeView::~ETabTreeView()
{
    for (int i = m_models.size() - 1; i <= 0; i--)
        delete m_models[i];
}

EItemModel* ETabTreeView::getModel(int modelIndex) const
{
    return m_models.at(modelIndex);
}

int ETabTreeView::addTabAndModel(const QString & text)
{
    int index = m_models.size();
    m_models.push_back(new EItemModel());
    m_tabs->addTab(text);
    return index;
}

int ETabTreeView::addTabAndModel(const QString & text, const QString & toolTip)
{
    int index = addTabAndModel(text);
    m_tabs->setTabToolTip(index, toolTip);
    return index;
}

void ETabTreeView::setTabText(int index, const QString & text)
{
    m_tabs->setTabText(index, text);
}

void ETabTreeView::setTabToolTip(int index, const QString & toolTip)
{
    m_tabs->setTabToolTip(index, toolTip);
}

void ETabTreeView::setCurrentModel(int modelIndex)
{
    m_tree->setModel(m_models.at(modelIndex));
}
