#include "EOptionDialog.h"

EOptionDialog::EOptionDialog(QJsonDocument * settings) :
    m_content       (new QWidget()),
    m_language      (new ELanguageSelector()),
    m_close         (new QPushButton(tr("Close"))),
    m_settings      (settings)
{
    QVBoxLayout *layout = new QVBoxLayout();

        layout->addWidget(m_content);
            QVBoxLayout *clayout = new QVBoxLayout();
            clayout->addWidget(m_language);
            m_content->setLayout(clayout);

        layout->addWidget(m_close);

    setLayout(layout);

    QObject::connect(m_close, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(m_language, SIGNAL(languageConfirmed(QString)), this, SLOT(changeLanguage(QString)));

    updateEnabled();
}

void EOptionDialog::updateEnabled()
{
    //If there is no given settings, this window is unusable.
    m_content->setEnabled( m_settings != nullptr );
}

void EOptionDialog::setSettingsFile(QJsonDocument *settings)
{
    m_settings = settings;
    updateEnabled();
}

void EOptionDialog::changeLanguage(const QString & language)
{
    QJsonObject newObject(m_settings->object());
    newObject["user language"] = language;
    m_settings->setObject(newObject);

    //Emit a signal which should update the json file
    emit languageChanged();

}
