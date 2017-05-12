#ifndef ESCROLLCANVAS_H
#define ESCROLLCANVAS_H

#include "ECanvas.h"
#include <QScrollBar>
#include <QGridLayout>


class EScrollCanvas : public QWidget
{
private :
    ECanvas *m_canvas;
    QScrollBar *m_HScroll;
    QScrollBar *m_VScroll;
public:
    EScrollCanvas();
    ECanvas* getCanvas() const {return m_canvas;}
};

#endif // ESCROLLCANVAS_H
