#ifndef ELEVELBUTTON_H
#define ELEVELBUTTON_H

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "EConstants.h"

class ELevelButton : public QPushButton
{
    Q_OBJECT

private :

public :
    ELevelButton(const QString & levelName);

public slots :
    void changeLevelName(const QString & levelName);

};

#endif // ELEVELBUTTON_H
