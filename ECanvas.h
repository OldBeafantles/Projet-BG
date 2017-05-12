#ifndef ECANVAS_H
#define ECANVAS_H

#include "QSFMLCanvas.h"
#include "BGHitbox.h"
#include "ESelection.h"

class ECanvas : public QSFMLCanvas
{

    Q_OBJECT

public :

    ECanvas(QWidget *Parent, const QPoint & Position, const QSize & Size, unsigned int frameTime = editor::FRAMETIME);

    //Vieilles fonctions à supprimer dans les plus brefs délais
    BGHitbox & getHitbox();
    void setHitbox(BGHitbox & hitbox);

private :

    void OnInit();

    void OnUpdate();

    BGHitbox mySprite;
    sf::Texture myTexture;
    ESelection m_selection;

    //This is declared here just to avoid allocation and destruction time, because it's used very frequently (see sf::Event::MouseMoved handle case)
    sf::Vector2i m_pixelPos;
    sf::Vector2f m_worldPos;

signals :

    //Passage par copie ?
    //Par pointeur ça risque de déconner. Essayer quand même.
    void selectionChanged(ESelection*);
    void mouseMoved(float x, float y);
};

#endif // ECANVAS_H
