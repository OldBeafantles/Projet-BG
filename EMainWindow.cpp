#include "EMainWindow.h"

EMainWindow::EMainWindow(const QString & levelName) :
    m_settings       (new QJsonDocument()),
    m_array          (new QAction* [NB_ACTIONS]),
    m_level          (new EScrollCanvas()),
    m_viewer         (new EObjectViewer()),
    m_lvlbtn         (new ELevelButton(levelName)),
    m_classSelector  (new ETabTreeView()),
    m_objectSelector (new ETreeView(0))
{
    //setWindowTitle(m_translator->operator[]("main").toObject()["title"].toString());
    setWindowTitle(tr("Project BG", "Name of the application"));


    // - Parameters file --------------------------------------------------------------------------------------------------------------------

    QString language;

    QFile settingsFile(editor::PARAMETERS_PATH + editor::SETTINGS_FILE);
    QString error;


    //If parameters file was successfully opened
    if (settingsFile.open(QIODevice::ReadOnly))
    {
        QJsonParseError *noidea = new QJsonParseError();
        *m_settings = QJsonDocument::fromJson(settingsFile.readAll(), noidea);

        if (noidea->error != QJsonParseError::NoError)
        {
            //If there was an error during the process
            error = noidea->errorString();
        }
        else
        {
            if (!m_settings->isObject())
            {
                error = editor::SETTINGS_FILE + " does not represent a JSON object";
            }
            else
            {
                QJsonValue value(m_settings->object()["user language"]);

                if (value == QJsonValue::Undefined || !value.isString())
                {
                    error = "\"user language\" is not a key in " + editor::SETTINGS_FILE + " or does not represent a string";
                }
                else
                {
                    //Finally, the only place where language is set...
                    language = value.toString();
                }

            }
        }

        delete noidea;
    }
    else
    {
        error = editor::SETTINGS_FILE + " could not be opened";
    }

    settingsFile.close();

    //If there was an error during the process, tries to use local language
    //(if there is an error, error string is not null, else it is, so we can use it that way)
    if (language.isEmpty())
    {
        language = QLocale::system().name().section('_', 0, 0);

        if (!error.isNull())
        {
            QMessageBox::warning(this, "Starting language", QString("Starting language could not be loaded.")
                                 + "\nError message : " + error
                                 + "\nLocal language (\"" + language + "\") will be loaded instead.");
        }
        //In the other case, language is not defined but Settings.json was correctly read, so we don't want to warn the user.
    }


    QTranslator translator;
    if (translator.load(editor::LANGUAGES_PATH + QString("projectBG_") + language))
    {
        qApp->installTranslator(&translator);
    }
    else if (language != "en") //There is no english file, because the program is already in english, so we do this.
    {
        QMessageBox::warning(this, "Starting language", QString("Language \"") + language + "\" could not be loaded. \nThe application will start in english.");
    }




    // - Widget construction ----------------------------------------------------------------------------------------------------------------


    //It isn't defined in separate classes because we want all its components to communicate with other widgets, such as ELevelWidget.
    //I didn't choose dock widgets because they propose too many functionnalities I don't want to handle
    //(such as repositionning, which can be problematic for visibility)
    //So all is done in one central widget.

    setStatusBar(new EStatusBar(levelName));

    QSplitter *central = new QSplitter(Qt::Orientation::Horizontal, this);
    central->setMinimumSize(editor::MAIN_MINIMUM_WIDTH, editor::MAIN_MINIMUM_HEIGHT);


        //First column of widgets -----------------------------------------------------------------
        //As we want it to be resizable by the user, we store it into a QSplitter.
        QSplitter *leftSplitter = new QSplitter(Qt::Orientation::Vertical);

            //Class selector (tree view to select a class, to create new objects instead of just editing existing ones)

                //Set tabs and models as well as some titles
                int index;
                index = m_classSelector->addTabAndModel(tr("Physical", "Tab 1 name"), tr("Open the list of physical objects, excluding characters", "tool tip tab 1"));
                m_classSelector->getModel(index)->addTitle({editor::ModelsTitles::Physical::COMMONSET,
                                                           editor::ModelsTitles::Physical::TILESET});

                    index = m_classSelector->addTabAndModel(tr("Non physical", "Tab 2 name"), tr("Open the list of non physical objects, such as gravity or detection areas", "tool tip tab 2"));
                    m_classSelector->getModel(index)->addTitle(editor::ModelsTitles::Non_physical::GRAVITY);

                    index = m_classSelector->addTabAndModel(tr("Characters", "Tab 3 name"), tr("Open the list of characters objects, which are typically ennemies", "tool tip tab 3"));

            leftSplitter->addWidget(m_classSelector);
            leftSplitter->setStretchFactor(leftSplitter->indexOf(m_classSelector), 1);

            //Object viewer (canvas which displays the selected objects)
            leftSplitter->addWidget(m_viewer);
            leftSplitter->setStretchFactor(leftSplitter->indexOf(m_viewer), 1);

            //Level button (which displays a dialog box to specify level properties)
            leftSplitter->addWidget(m_lvlbtn);
            leftSplitter->setStretchFactor(leftSplitter->indexOf(m_lvlbtn), 0);
            m_lvlbtn->setShortcut(QKeySequence(tr("Alt+L", "level button shortcut")));
            m_lvlbtn->setToolTip(tr("Click here to see and edit the properties of the current level.", "level button tool tip"));

        central->addWidget(leftSplitter);


        //Second column of widgets ----------------------------------------------------------------

            //Level canvas (with scroll bars)
            central->addWidget(m_level);


        //Third column of widgets -----------------------------------------------------------------

            //Object selector (right tree view)
            central->addWidget(m_objectSelector);

            EItemModel *objectModel = new EItemModel();
            //Add dedicated titles to the model...
            objectModel->addTitle({editor::ModelsTitles::Objects::GROUPS,
                                  editor::ModelsTitles::Objects::INVISIBLE,
                                  editor::ModelsTitles::Objects::HIDDEN,
                                  editor::ModelsTitles::Objects::ALL});

            //... and set it as m_objectSelector's model
            m_objectSelector->getTreeView()->setModel(objectModel);



    //Set size coefficients (widgets can be resized though)
    central->setSizes(editor::MAIN_HORIZONTAL_BASE_SIZE);

    //Set the central widget as the actual central widget
    setCentralWidget(central);

    // - Connexions -------------------------------------------------------------------------------------------------------------------------

    /* Here is some information about connections. Maybe it's not complete.
         *
     * EScrollCanvas :
         * send :    - selectionChanged
         *           - cursorMoved
         *           -
         * receive : - selectionChanged
         *
     * EStatusBar :
         * send :    -
         * receive : - levelChanged
         *           - mouseMoved
         *           - selectionChanged
         *
     * EObjectViewer :
         * send :    -
         * receive : - selectionChanged
         *
     * ELevelButton (was deleted but maybe relevant later, to do its slots) :
         * send :    -
         * receive : - levelChanged
         *
     * ETabTreeView :
         * send :    - selectionChanged
         * receive : - selectionChanged (to unselect its previously selected object)
         *
     * ETreeView (object selector) :
         * send :    - selectionChanged
         * receive : - selectionChanged
         *           - objectCreated
         *
     * Tool and menu bars :
        * send :    - a lot of things
        * receive : - selectionChanged (because they are disabled by strong focus)
     * */

    /* So for now custom signals are :
     * - selectionChanged
     * - mouseMoved
     * - levelChanged
     * - objectCreated
     * They should have the same name accross the classes. Maybe this should be done with multi-inheritance.
     * */

    //Class selector

    //Canvas

    //Changes X and Y on the status bar, depending on where the mouse is
    QObject::connect(m_level->getCanvas(), SIGNAL(mouseMoved(float, float)), statusBar(), SLOT(changeXY(float, float)));


    // - Display initializations ------------------------------------------------------------------------------------------------------------

    //Initialize tool and menu bars
    initActions();

    //Here add a signal (or a treatment that sends it) to initialize all the widgets.
    //Opening a level should fit.

    //Exceptions treatment test
    //QString lol = actions[EActionArray::EMainAction::NB_ACTIONS]->whatsThis();
    //QMessageBox::information(this, "Debug", QString::number(m_translator->getValues()->operator[]("lol").toInt()));
}


EMainWindow::~EMainWindow()
{
    delete m_settings;
    delete[] m_array;
}

void EMainWindow::test()
{
    QWidget *poorDialog = new QWidget();

        QVBoxLayout *layout = new QVBoxLayout();

        BGHitbox hitbox;
        hitbox.addPoint(BGPoint(30, 30));
        hitbox.addPoint(BGPoint(300, 30));
        hitbox.addPoint(BGPoint(165, 165));
        //hitbox.autoFinish();

        EHitboxDialog *dialog = new EHitboxDialog(hitbox);
        layout->addWidget(dialog);

        //Change this button. There should be at least two buttons : "Ok" and "Cancel".
        //By the way, this window isn't a real dialog, it's not even modal.
        QPushButton *lol = new QPushButton("Ok");
        layout->addWidget(lol);

        poorDialog->setLayout(layout);

    QObject::connect(lol, SIGNAL(clicked()), poorDialog, SLOT(close()));
    poorDialog->setWindowTitle("Hitbox edition");
    poorDialog->show();
}

void EMainWindow::openOptions() const
{
    EOptionDialog *dialog = new EOptionDialog(m_settings);
    dialog->setModal(true);
    dialog->setWindowTitle(tr("Options", "name of options window"));
    QObject::connect(dialog, SIGNAL(languageChanged()), this, SLOT(updateSettingsFile()));
    dialog->show();
}

void EMainWindow::updateSettingsFile() const
{
    QFile settingsFile(editor::PARAMETERS_PATH + editor::SETTINGS_FILE);
    if (settingsFile.open(QIODevice::WriteOnly))
    {
        settingsFile.write(m_settings->toJson());
    }
}
