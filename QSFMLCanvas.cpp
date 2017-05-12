#include "QSFMLCanvas.h"
#include <QMessageBox>

QSFMLCanvas::QSFMLCanvas(QWidget *Parent, const QPoint & Position, const QSize & Size, unsigned int FrameTime) :
    QWidget            (Parent),
    myInitialized      (false)
{
    // Setup some states to allow direct rendering into the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);

    // Setup the widget geometry
    move(Position);
    resize(Size);

    // Setup the timer
    myTimer.setInterval(FrameTime);

    //Additionnal attribute, for tests
    frameTime = FrameTime;
    myInitialized = false;
}

#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif

void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!myInitialized)
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif

        // Create the SFML window with the widget handle
        sf::RenderWindow::create((sf::WindowHandle) winId());

        // Let the derived class do its specific stuff
        OnInit();

        // Setup the timer to trigger a refresh at specified framerate
        connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        myTimer.start();

        myInitialized = true;
    }
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return 0;
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
    // Let the derived class do its specific stuff
    OnUpdate();

    // Display on screen
    sf::RenderWindow::display();
}

void QSFMLCanvas::resize(const QSize & size)
{
    //QMessageBox::information(this, "Debug", "lol");
    setBaseSize(size);
    //Readjust render window here
}

void QSFMLCanvas::resizeWidth(int width)
{
    resize(QSize(width, baseSize().height()));
}

void QSFMLCanvas::resizeHeight(int height)
{
    resize(QSize(baseSize().height(), height));
}
