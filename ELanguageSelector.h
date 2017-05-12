#ifndef ELANGUAGESELECTOR_H
#define ELANGUAGESELECTOR_H

#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QDir>
//#include <QFileInfo>
#include "EConstants.h"

class ELanguageSelector : public QGroupBox
{
    Q_OBJECT

private:
    QComboBox   *m_choice;
    QPushButton *m_btn;

public:
    ELanguageSelector();

    QComboBox* getComboBox() const;
    QPushButton* getButton() const;

public slots:
    void confirm();

signals:
    void languageConfirmed(const QString &);
};

#endif // ELANGUAGESELECTOR_H
