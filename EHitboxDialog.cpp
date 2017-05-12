#include "EHitboxDialog.h"

EHitboxDialog::EHitboxDialog(BGHitbox & _hitbox) :
    m_canvas        (new EScrollCanvas()),
    //m_hitbox        (_hitbox),
    m_HSlider       (new QSlider(Qt::Orientation::Horizontal)),
    m_VSlider       (new QSlider(Qt::Orientation::Vertical)),
    m_indexSpb      (new QSpinBox()),
    m_numberSpb     (new QSpinBox()),
    m_insertBtn     (new QPushButton(tr("&Insert", "Inserts a point between two existing ones"))),
    m_delBtn        (new QPushButton(tr("&Delete", "Delete the current point"))),
    m_XSpb          (new QSpinBox()),
    m_YSpb          (new QSpinBox())
{
    QVBoxLayout *mainLayout = new QVBoxLayout();


    // - First group of widget (canvas relative) --------------------------------------------------------------------------------------------

    QWidget *grpCanvas = new QWidget();

        QGridLayout *cvsLayout = new QGridLayout();

        //Canvas
        m_canvas->getCanvas()->setMinimumSize(QSize(200, 200));
        m_canvas->getCanvas()->setHitbox(_hitbox);
        cvsLayout->addWidget(m_canvas, 1, 1);

        //Sliders
        m_HSlider->setMinimum(200);
        m_HSlider->setMaximum(800);
        cvsLayout->addWidget(m_HSlider, 0, 1);
        m_VSlider->setMinimum(200);
        m_VSlider->setMaximum(800);
        cvsLayout->addWidget(m_VSlider, 1, 0);

        grpCanvas->setLayout(cvsLayout);

    mainLayout->addWidget(grpCanvas);


    // - Point position group ---------------------------------------------------------------------------------------------------------------

    QGroupBox *grpPos = new QGroupBox(tr("Point position"));

        QHBoxLayout *posLayout = new QHBoxLayout();

        //X
        m_XSpb->setToolTip(tr("Set the horizontal position of the current point"));
        QLabel *xLabel = new QLabel("X:");
        xLabel->setAlignment(Qt::AlignRight);
        posLayout->addWidget(xLabel, 0);
        posLayout->addWidget(m_XSpb, 1);

        //Y
        m_YSpb->setToolTip(tr("Set the vertical position of the current point"));
        QLabel *yLabel = new QLabel("Y:");
        yLabel->setAlignment(Qt::AlignRight);
        posLayout->addWidget(yLabel, 0);
        posLayout->addWidget(m_YSpb, 1);

        grpPos->setLayout(posLayout);

    mainLayout->addWidget(grpPos);


    // - Points number group ----------------------------------------------------------------------------------------------------------------

    QGroupBox *grpNumber = new QGroupBox(tr("Points"));

        QGridLayout *numLayout = new QGridLayout();

        //Point index label
        numLayout->addWidget(new QLabel(tr("Point index:")), 0, 0);

        //Point index spinbox
        m_indexSpb->setToolTip(tr("Index of the current point"));
        numLayout->addWidget(m_indexSpb, 0, 1);

        //Number of points label
        numLayout->addWidget(new QLabel(tr("Number of points:")), 1, 0);

        //Number of points spinbox
        m_numberSpb->setToolTip(tr("Set the total number of points"));
        numLayout->addWidget(m_numberSpb, 1, 1);

        //Insert point button
        m_insertBtn->setToolTip(tr("Insert a new point with the current index. The current point takes the next index."));
        numLayout->addWidget(m_insertBtn, 2, 0);

        //Delete point button
        m_delBtn->setToolTip(tr("Delete the current point"));
        numLayout->addWidget(m_delBtn, 2, 1);

        grpNumber->setLayout(numLayout);

    mainLayout->addWidget(grpNumber);
    setLayout(mainLayout);

    //Current point changes
    QObject::connect(m_indexSpb, SIGNAL(valueChanged(int)), this, SLOT(setCurrentPoint(int)));
    //QObject::connect(m_canvas->getCanvas(), SIGNAL(selectionChanged(ESelection*)), this, SLOT(findAndSetCurrentPoint(ESelection*));

    //Position modifiers
    QObject::connect(m_XSpb, SIGNAL(valueChanged(int)), this, SLOT(setCurrentPointX(int)));
    QObject::connect(m_YSpb, SIGNAL(valueChanged(int)), this, SLOT(setCurrentPointY(int)));
}

BGHitbox & EHitboxDialog::getHitbox() const
{
    return m_canvas->getCanvas()->getHitbox();
}

/*void EHitboxDialog::setCurrentPoint(int index) const
{
    getHitbox().setCurrentPoint((char) index);
}

void EHitboxDialog::setCurrentPointPosition(int x, int y) const
{
    getHitbox().movePoint(BGPoint(getHitbox().quelque_chose(getHitbox().getCurrentPoint()).x(),
                                  getHitbox().quelque_chose(getHitbox().getCurrentPoint()).y()),
                          getHitbox().getCurrentPoint());
}

void EHitboxDialog::setCurrentPointX(int x) const
{
    getHitbox().movePoint(BGPoint(x, getHitbox().quelque_chose(getHitbox().getCurrentPoint()).y()), getHitbox().getCurrentPoint());
}

void EHitboxDialog::setCurrentPointY(int y) const
{
    getHitbox().movePoint(BGPoint(getHitbox().quelque_chose(getHitbox().getCurrentPoint()).x(), y), getHitbox().getCurrentPoint());
}*/

/*void EHitboxDialog::addPoint() const
{
    // XD
    setCurrentPoint(m_hitbox.size());
}*/

/*void EHitboxDialog::insertPoint(int index) const
{
    addPoint();
    setCurrentPoint(index);
}*/

/*void EHitboxDialog::findAndSetCurrentPoint(ESelection *selection)
{
    int index = m_hitbox.findPointIndex(selection.getX(), selection.getY());

    //If a point is found, set it as the current point
    if (index != -1)
        setCurrentPoint(ind);
}
*/
