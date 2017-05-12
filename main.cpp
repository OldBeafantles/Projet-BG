#include <QApplication>
#include "EMainWindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    //Splitter handles are invisible without this line.
    app.setStyleSheet("QSplitter::handle { background-color: gray } "); //Ugly

    try
    {
        //Create the main window
        EMainWindow *emain = new EMainWindow("TestLevel");
        emain->show();
    }
    catch (EException & e)
    {
        if (e.what(0) == QMessageBox::Ok)
            app.quit(); //Doesn't work : application still running
    }


    return app.exec();
}
