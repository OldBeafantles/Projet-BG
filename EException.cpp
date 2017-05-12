#include "EException.h"

EException::EException(QString body)
{
    m_body = body;
}

int EException::what(QWidget *parent, const QString & title) const
{
    return QMessageBox::critical(parent, title, m_body);
}
