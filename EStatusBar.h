#ifndef ESTATUSBAR_H
#define ESTATUSBAR_H

#include <QStatusBar>
#include <QLabel>
#include "EConstants.h"

class EStatusBar : public QStatusBar
{
    Q_OBJECT

private :
    QLabel *m_xLabel;
    QLabel *m_yLabel;
    QLabel *m_lvlLabel;

    static const QString m_XTEXT;
    static const QString m_YTEXT;
    static const QString m_LVLTEXT;

    static const double m_XYCOEF;
    static const double m_LVLCOEF;


public :
    EStatusBar(const QString & levelName);

public slots :
    void changeX(float x) const;
    void changeY(float y) const;
    void changeXY(float x, float y) const;
    void changeLevelName(QString name) const;
    void changeWidth(int width) const;

};

#endif // ESTATUSBAR_H
