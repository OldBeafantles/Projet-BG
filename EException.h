#ifndef EEXCEPTION_H
#define EEXCEPTION_H

#include "EConstants.h"
#include <QMessageBox>

class EException
{
private :
    QString m_body;

public :
    EException(QString body);
    int what(QWidget *parent, const QString & title = editor::EXCEPTION_TITLE) const;
};

#endif // EEXCEPTION_H
