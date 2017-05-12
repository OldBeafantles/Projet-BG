#ifndef EHITBOXEDITOR_H
#define EHITBOXEDITOR_H

#include <QWidget>
#include <QScrollBar>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include "EScrollCanvas.h"
#include "BGHitbox.h"

class EHitboxDialog : public QWidget
{
    Q_OBJECT

private :
    EScrollCanvas     *m_canvas;

    //BGHitbox        *m_hitbox;

    //Resizers
    QSlider         *m_HSlider;
    QSlider         *m_VSlider;

    //Points number controllers
    QSpinBox        *m_indexSpb;
    QSpinBox        *m_numberSpb;
    QPushButton     *m_insertBtn;
    QPushButton     *m_delBtn;

    //Point position controllers
    QSpinBox        *m_XSpb;
    QSpinBox        *m_YSpb;


public :
    //This constructor should have as argument a pointer to a hitbox. If it's null, it starts with a default hitbox (three points at least).
    EHitboxDialog(BGHitbox &_hitbox);

    BGHitbox & getHitbox() const;

public slots :

    //Point position changes
    //void setCurrentPointPosition(int x, int y) const;
    //void setCurrentPointX(int x) const;
    //void setCurrentPointY(int y) const;

    //Add point
    //void addPoint() const;
    //void insertPoint(int index) const;

    //Detect point
    //void findAndSetCurrentPoint(ESelection *selection);

};

#endif // EHITBOXEDITOR_H
