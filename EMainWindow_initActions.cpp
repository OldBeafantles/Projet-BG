#include "EMainWindow.h"

void EMainWindow::initActions()
{
    //Initialize the whole array
    //Build the menu and tool bars
    //And connect all is needed
    m_toolBar = addToolBar(tr("Tool bar", "tool bar name"));
    QMenu *currentMenu;

    // - File menu --------------------------------------------------------------------------------------------------------------------------
    currentMenu = menuBar()->addMenu(tr("&File", "menu 1 name"));

    //NEW -------------------------------------------------
    m_array[NEW] = new QAction(QIcon(editor::ICON_PATH + "New.png"), tr("New level"));
    m_array[NEW]->setShortcut(QKeySequence(tr("Ctrl+N", "New level shortcut")));
    currentMenu->addAction(m_array[NEW]);
    m_toolBar->addAction(m_array[NEW]);
    //Connect here

    //OPEN ------------------------------------------------
    m_array[OPEN] = new QAction(QIcon(editor::ICON_PATH + "Open.png"), tr("Open level"));
    m_array[OPEN]->setShortcut(QKeySequence(tr("Ctrl+O", "open level shortcut")));
    currentMenu->addAction(m_array[OPEN]);
    m_toolBar->addAction(m_array[OPEN]);
    //Connexions

    //SAVE ------------------------------------------------
    m_array[SAVE] = new QAction(QIcon(editor::ICON_PATH + "Save.png"), tr("Save"));
    m_array[SAVE]->setShortcut(QKeySequence(tr("Ctrl+S", "save level shortcut")));
    currentMenu->addAction(m_array[SAVE]);
    m_toolBar->addAction(m_array[SAVE]);
    //Connexions

    m_toolBar->addSeparator();

    //SAVE_AS ---------------------------------------------
    m_array[SAVE_AS] = new QAction(tr("Save as...")); //+icon
    m_array[SAVE_AS]->setShortcut(QKeySequence(tr("Ctrl+Alt+S", "save as... shortcut")));
    currentMenu->addAction(m_array[SAVE_AS]);
    //Connexions

    currentMenu->addSeparator();

    //CLOSE -----------------------------------------------
    m_array[CLOSE] = new QAction(tr("Close level")); //+icon
    m_array[CLOSE]->setShortcut(QKeySequence(tr("Ctrl+C", "close level shortcut")));
    currentMenu->addAction(m_array[CLOSE]);
    //Connexions

    currentMenu->addSeparator();

    //QUIT ------------------------------------------------
    m_array[QUIT] = new QAction(tr("Quit"));
    m_array[QUIT]->setShortcut(QKeySequence(tr("Ctrl+Q", "quit shortcut")));
    currentMenu->addAction(m_array[QUIT]);
    //Change the connection (warning message to save file, if not done) !
    QObject::connect(m_array[QUIT], SIGNAL(triggered()), qApp, SLOT(quit()));


    // - TEST -------------------------------------------------------------------------------------------------------------------------------

    m_toolBar->addSeparator();

    m_array[TEST] = new QAction(QIcon(editor::ICON_PATH + "Test.png"), "Test");
    m_array[TEST]->setShortcut(QKeySequence("Ctrl+Shift+T"));
    m_toolBar->addAction(m_array[TEST]);
    QObject::connect(m_array[TEST], SIGNAL(triggered()), this, SLOT(test()));


    // - Edit menu --------------------------------------------------------------------------------------------------------------------------
    currentMenu = menuBar()->addMenu(tr("&Edit", "menu 2 name"));


    // - Option menu ------------------------------------------------------------------------------------------------------------------------
    currentMenu = menuBar()->addMenu(tr("&Options", "menu 3 name"));

    //OPTION ----------------------------------------------
    m_array[OPTIONS] = new QAction(tr("Options"));
    //m_array[OPTIONS]->setShortcut(QKeySequence(""));
    currentMenu->addAction(m_array[OPTIONS]);
    QObject::connect(m_array[OPTIONS], SIGNAL(triggered()), this, SLOT(openOptions()));
}
