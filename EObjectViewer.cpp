#include "EObjectViewer.h"

EObjectViewer::EObjectViewer() :
    m_properties    (new QPushButton(tr("&Properties", "button which allows to see the selected object's properties"))),
    m_canvas        (new ECanvas(0, QPoint(0, 0), QSize(100, 100)))
{
    m_canvas->setMinimumHeight(64);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(m_canvas);
    layout->addWidget(m_properties);

    setLayout(layout);
}
