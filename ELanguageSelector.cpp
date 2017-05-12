#include "ELanguageSelector.h"

ELanguageSelector::ELanguageSelector() :
    m_choice    (new QComboBox()),
    m_btn       (new QPushButton("Ok"))
{
    QGridLayout *layout = new QGridLayout();

        QLabel *label = new QLabel(tr("Available languages:"));
        layout->addWidget(label, 0, 0);

        layout->addWidget(m_choice, 0, 1);
        layout->addWidget(m_btn, 0, 2);

        QLabel *labelLocal = new QLabel(tr("Local : ") + QLocale::system().name().section('_', 0, 0));
        layout->addWidget(labelLocal, 1, 0);

        QLabel *labelDefault = new QLabel(tr("Default : en"));
        layout->addWidget(labelDefault, 1, 1);

        for (int i = 0; i < layout->columnCount(); i++)
        {
            layout->setColumnStretch(i, 1);
        }

    setLayout(layout);

    setTitle(tr("Language", "title of the group box used to select a language"));
    m_btn->setToolTip(tr("Set the selected language as the one to load at the start of the application"));

    //List the different available language files
    QStandardItemModel *model = new QStandardItemModel();

        //Looks for correct files
        QDir dir(editor::LANGUAGES_PATH);
        QStringList files( dir.entryList({"projectBG_*.qm"}) );

        //We immediately add "en" item, because there are no corresponding file
        model->appendRow(new QStandardItem("en"));

        QString added;

        for (int i = 0; i < files.size(); i++)
        {
            //Remove .qm
            added = files[i].remove(".qm");
            //And remove all the stuff behind '_' included
            //Formula : last index - last index of "_" (which is supposed to be just behind the subtring we are interested for)
            //last index = size - 1
            added = added.right(added.size() - 1 - added.lastIndexOf("_"));

            model->appendRow(new QStandardItem(added));
        }

        m_choice->setModel(model);


    QObject::connect(m_btn, SIGNAL(clicked()), this, SLOT(confirm()));

}

QComboBox* ELanguageSelector::getComboBox() const
{
    return m_choice;
}

QPushButton* ELanguageSelector::getButton() const
{
    return m_btn;
}

void ELanguageSelector::confirm()
{
    //Get the current selected item in m_choice.
    QString text(m_choice->itemText(m_choice->currentIndex()));

    int confirmed = QMessageBox::question(this, tr("Confirm starting language"), tr("Are you sure you want to set %1 as your starting language file ?", "%1 represents the new starting language").arg(text),
                                          QMessageBox::Yes | QMessageBox::No);

    if (confirmed == QMessageBox::Yes)
    {
        emit languageConfirmed(text);
        QMessageBox::information(0, tr("Settings modified"), tr("Application will automatically update at its start."));
    }
}
