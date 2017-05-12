#ifndef EOPTIONDIALOG_H
#define EOPTIONDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "ELanguageSelector.h"

class EOptionDialog : public QDialog
{
    Q_OBJECT

private :

    //A widget used to disable all other widgets, except m_close.
    QWidget             *m_content;
    ELanguageSelector   *m_language;
    QPushButton         *m_close;
    QJsonDocument       *m_settings;

    void updateEnabled();

public :
    EOptionDialog(QJsonDocument *settings = nullptr);

    void setSettingsFile(QJsonDocument *settings);

public slots :
    void changeLanguage(const QString & language);

signals :
    void languageChanged();
};

#endif // EOPTIONDIALOG_H
