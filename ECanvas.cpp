#include "ECanvas.h"

ECanvas::ECanvas(QWidget *Parent, const QPoint & Position, const QSize & Size, unsigned int frameTime) :
    QSFMLCanvas(Parent, Position, Size, frameTime),
    m_selection         (ESelection())
{

}

BGHitbox & ECanvas::getHitbox()
{
    return mySprite;
}

void ECanvas::setHitbox(BGHitbox & hitbox)
{
    mySprite = hitbox;
    //draw(hitbox.showHitboxContent());
}

void ECanvas::OnInit()
{
    // Load the image
    myTexture.loadFromFile("D:/Toi/Documents/Programmes/C++/Jeux/Projet_BG/ImageTest.png");

    // Setup the sprite
    //mySprite.setTexture(myTexture);
    //mySprite.setTextureRect(sf::IntRect(0,0,64,64));
    //mySprite.setPosition(36,36);
}

void ECanvas::OnUpdate()
{
    // Clear screen
    clear(sf::Color(0, 128, 0));
    mySprite.draw(LINES | POINTS | CURRENT_POINT | HITBOX_CONTENT, *this);


    sf::Event event;

    while (pollEvent(event))
    {

        switch (event.type)
        {       
            //Send info about position in the cursor. This is actually useful only for EStatusBar.
            case sf::Event::MouseMoved:
                m_pixelPos = sf::Mouse::getPosition(*this);
                m_worldPos = mapPixelToCoords(m_pixelPos);
                emit mouseMoved(m_worldPos.x, m_worldPos.y);
                //emit mouseMoved(event.mouseMove.x, event.mouseMove.y);
                break;

            //Left mouse button pressed means a new selection.
            //Except if the current selection is a class and not an object, in this case it will create a new object.
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    m_selection.setPosition(event.mouseButton.x, event.mouseButton.y);
                    emit selectionChanged(&m_selection);
                }
                break;

            //If the mouse leaves a canvas, the position isn't valid anymore.
            case sf::Event::MouseLeft:
                m_selection.setNoPosition();
                break;

            //When the canvas is resized, then it showed more than before : there's no zoom or dezoom in this case (unlike game canvas)
            case sf::Event::Resized:
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                setView(sf::View(visibleArea));
                break;
            }

            default:
                break;
        }
    }
}
