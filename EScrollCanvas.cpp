#include "EScrollCanvas.h"

EScrollCanvas::EScrollCanvas() :
    m_canvas        (new ECanvas(0, QPoint(0,0), QSize(0,0))),
    m_HScroll       (new QScrollBar(Qt::Orientation::Horizontal)),
    m_VScroll       (new QScrollBar(Qt::Orientation::Vertical))
{
    //Create the layout
    QGridLayout *layout = new QGridLayout(this);

    //Create the main widgets
    //Organize all widgets
    layout->addWidget(m_canvas, 0, 0);
    layout->addWidget(m_HScroll, 1, 0);
    layout->addWidget(m_VScroll, 0, 1);

    this->setLayout(layout);

    //Connect widgets between them
    // To scroll obviously, but also to disable scroll bars when the level is smaller than the canvas, maybe more.
}
