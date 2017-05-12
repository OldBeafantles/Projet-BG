#include "EStatusBar.h"

const QString EStatusBar::m_XTEXT = QString(tr("X: ", "status bar position label"));
const QString EStatusBar::m_YTEXT = QString(tr("Y: ", "status bar position label"));
const QString EStatusBar::m_LVLTEXT = QString(tr("Level: ", "introduces the name of the level in the status bar"));

const double EStatusBar::m_XYCOEF = 1.0/13.0;
const double EStatusBar::m_LVLCOEF = 1.0/5.0;

EStatusBar::EStatusBar(const QString & levelName) :
    m_xLabel    (new QLabel(m_XTEXT + "0")),
    m_yLabel    (new QLabel(m_YTEXT + "0")),
    m_lvlLabel  (new QLabel(m_LVLTEXT + levelName))
{
    //Set the minimum sizes for labels
    m_xLabel->setMinimumWidth((int) (m_XYCOEF * editor::MAIN_MINIMUM_WIDTH));
    m_yLabel->setMinimumWidth((int) (m_XYCOEF * editor::MAIN_MINIMUM_WIDTH));
    m_lvlLabel->setMinimumWidth((int) (m_LVLCOEF * editor::MAIN_MINIMUM_WIDTH));

    //Display the widgets on the status bar
    addPermanentWidget(m_lvlLabel, 0);
    addPermanentWidget(m_xLabel, 0);
    addPermanentWidget(m_yLabel, 0);
}

void EStatusBar::changeX(float x) const
{
    m_xLabel->setText(m_XTEXT + QString::number(x, 'f', 0));
}

void EStatusBar::changeY(float y) const
{
    m_yLabel->setText(m_YTEXT + QString::number(y, 'f', 0));
}

void EStatusBar::changeXY(float x, float y) const
{
    changeX(x);
    changeY(y);
}

void EStatusBar::changeLevelName(QString name) const
{
    m_lvlLabel->setText(m_LVLTEXT + name);
}

void EStatusBar::changeWidth(int width) const
{
    m_xLabel->setMinimumWidth((int) (width * m_XYCOEF));
    m_yLabel->setMinimumWidth((int) (width * m_XYCOEF));
    m_lvlLabel->setMinimumWidth((int) (width * m_LVLCOEF));
}

