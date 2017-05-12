#ifndef EMAINWINDOW_H
#define EMAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QSplitter>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonObject>
#include <QTranslator>
#include "EException.h"
#include "EScrollCanvas.h"
#include "EStatusBar.h"
#include "EObjectViewer.h"
#include "ELevelButton.h"
#include "ETabTreeView.h"
#include "EHitboxDialog.h"
#include "EOptionDialog.h"


class EMainWindow : public QMainWindow
{
    Q_OBJECT

private :

    QJsonDocument       *m_settings;

    //Actions-relative attributes
    //m_array was originally in an other class, so its name is not well fitting in EMainWindow.
    //It's an array of QAction (used by both tool and menu bars)
    QAction             **m_array;
    QToolBar            *m_toolBar;

    //Main widgets
    EScrollCanvas       *m_level;
    EObjectViewer       *m_viewer;
    ELevelButton        *m_lvlbtn;
    ETabTreeView        *m_classSelector;
    ETreeView           *m_objectSelector;

    //Initialize tool and menu bars. Called only in the constructor (they were separated because of lisibility)
    void initActions();

public :

    //Constructor
    //Later, add as parameter a level to initialize all values such as levelName, or properties,
    //and the parameter object (which has to read parameter file).
    //This level will replace the QString argument.
    EMainWindow(const QString & levelName);
    ~EMainWindow();

    enum EMainAction
    {
        //File management
        NEW,
        OPEN,
        SAVE,
        SAVE_AS,
        CLOSE,

        //No idea of how I should name this section
        QUIT,
        //OPEN_NEW_WINDOW,

        //Option choices
        OPTIONS,

        //Test (so it shouldn't be in release versions)
        TEST,

        //Number of actions
        NB_ACTIONS
    };

public slots :
    //The unique purpose of this method is to test some new widget.
    //This shouldn't be in release versions.
    //It's associated with TEST action.
    void test();

    void openOptions() const;

    void updateSettingsFile() const;

signals :
    //A signal meant to be send to all the widgets that are part of the main window.
    //Should send a selection object (selection state is deductible from this)
    //If it's not the case, just send the selection and the selection state, but it could be nicer.
    void selectionChanged(ESelection*);

};

#endif // EMAINWINDOW_H
