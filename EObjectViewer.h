#ifndef EOBJECTVIEWER_H
#define EOBJECTVIEWER_H

#include <QPushButton>
#include <QVBoxLayout>
#include "ECanvas.h"

class EObjectViewer : public QWidget
{
    Q_OBJECT

private :
    QPushButton *m_properties;
    ECanvas *m_canvas;

public :
    EObjectViewer();

//public slots :
    //void changeObject(GVisible);

};

#endif // EOBJECTVIEWER_H
