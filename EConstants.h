#ifndef ECONSTANTS_H
#define ECONSTANTS_H

#include <QString>
#include <QSize>
#include <QList>

namespace editor
{
    // - Path -------------------------------------------------------------------------------------------------------------------------------

    const QByteArray EDITOR_PATH("Editor\\");
    const QByteArray ICON_PATH(EDITOR_PATH + "Icons\\");
    const QByteArray PARAMETERS_PATH(EDITOR_PATH + "Parameters\\");
    const QByteArray LANGUAGES_PATH(PARAMETERS_PATH + "Languages\\");


    // - Widget proportions -----------------------------------------------------------------------------------------------------------------

    // - Main window --------------------------------------

    //Minimum size at beginning. This does not stand for the main window but for its central widget.
    const int MAIN_MINIMUM_WIDTH = 880;
    const int MAIN_MINIMUM_HEIGHT = 480;

    //Horizontal size coefficients
    const double RIGHT_COLUMN_WIDTH_COEF = 1.0/20.0;
    const double LEFT_COLUMN_WIDTH_COEF = RIGHT_COLUMN_WIDTH_COEF;
    const double MIDDLE_COLUMN_WIDTH_COEF = 1.0 - RIGHT_COLUMN_WIDTH_COEF - LEFT_COLUMN_WIDTH_COEF;

    //Horizontal widgets base size
    //Those constants are deducted from the previous ones and are the only ones to be used in code.
    //Possible improvment : store the coefficients into a parameter file (in that way, user arrangements are kept)
    const QList<int> MAIN_HORIZONTAL_BASE_SIZE = {(int) (RIGHT_COLUMN_WIDTH_COEF * MAIN_MINIMUM_WIDTH),
                                                  (int) (MIDDLE_COLUMN_WIDTH_COEF * MAIN_MINIMUM_WIDTH),
                                                  (int) (LEFT_COLUMN_WIDTH_COEF * MAIN_MINIMUM_WIDTH)
                                                  };

    // - Models' title ----------------------------------------------------------------------------------------------------------------------
    //A list of constants
    //In order to be displayed, each constant needs to be added in a model directly in EMainWindow.cpp...
    // (or other widgets such as EHitboxDialog, ETilesetWindow, ...)

    //tr does not work on constant expressions...
    namespace ModelsTitles
    {
        namespace Physical
        {
            const QString COMMONSET(QObject::tr("Commonset", "One of the titles in tree views"));
            const QString TILESET(QObject::tr("Tileset", "One of the titles in tree views"));
        }

        namespace Non_physical
        {
            //Maybe not useful, except for tests
            const QString GRAVITY(QObject::tr("Gravity aeras", "One of the titles in tree views"));
        }

        namespace Objects
        {
            const QString GROUPS(QObject::tr("Groups", "One of the titles in tree views"));
            const QString INVISIBLE(QObject::tr("Invisible", "One of the titles in tree views"));
            const QString HIDDEN(QObject::tr("Hidden", "One of the titles in tree views"));
            const QString ALL(QObject::tr("All", "One of the titles in tree views"));
        }
    }

    // - Miscellaneous ----------------------------------------------------------------------------------------------------------------------
    const unsigned int FRAMETIME = 0.02;

    const QString EXCEPTION_TITLE(QObject::tr("Critical error"));

    const QString SETTINGS_FILE("Settings.json");
}

#endif // ECONSTANTS_H
