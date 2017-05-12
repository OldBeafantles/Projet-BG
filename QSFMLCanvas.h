/* https://github.com/SFML/SFML/wiki/Tutorial%3A-Integrating-SFML-into-Qt */

#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <SFML/Graphics.hpp>
#include <QWidget>
#include <QTimer>
#include "EConstants.h"

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
    Q_OBJECT

public :

    QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = editor::FRAMETIME);

    //virtual ~QSFMLCanvas();

    unsigned int getFrameTime() const {return frameTime;}

private :

    virtual void OnInit()=0;

    virtual void OnUpdate()=0;

    virtual QPaintEngine* paintEngine() const;

    virtual void showEvent(QShowEvent*);

    virtual void paintEvent(QPaintEvent*);

    QTimer myTimer;
    bool   myInitialized;

    unsigned int frameTime;

public slots :

    void resize(const QSize & size);

    void resizeWidth(int width);

    void resizeHeight(int height);

};

#endif // QSFMLCANVAS_H
