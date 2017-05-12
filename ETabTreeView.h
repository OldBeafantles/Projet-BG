#ifndef ETABCLASSSELECTOR_H
#define ETABCLASSSELECTOR_H

#include <QTabBar>
#include <vector>
#include "ETreeView.h"


//This widget associates each tab you create on him with a model.
//Selecting a tab changes tree view's current model.

class ETabTreeView : public ETreeView
{
    Q_OBJECT

private :
    QTabBar *m_tabs;
    std::vector<EItemModel*> m_models;

public :
    ETabTreeView();
    ~ETabTreeView();

    //ETabTreeView provides no direct access to its QTabBar, because that could lead to the creation of a new tab
    //while there is no correspondant model.
    EItemModel* getModel(int modelIndex) const;

    //Add in the same time a tab and its corresponding model,
    //and return their index.
    int addTabAndModel(const QString & text);
    int addTabAndModel(const QString & text, const QString & toolTip);

public slots :

    void setTabText(int index, const QString & text);
    void setTabToolTip(int index, const QString & toolTip);

    void setCurrentModel(int modelIndex);

};

#endif // ETABCLASSSELECTOR_H
