#include <iostream>
#include "BGHitbox.h"
#include "BGPolygon.h"
#include "BGSegment.h"
#include "BGTriangle.h"
#include "BGPoint.h"
#include <SFML/Graphics.hpp>

int main()
{
	//Quelques tests pour vérifier que je n'ai pas fait d'erreurs

	BGHitbox h;

	h.addPoint(BGPoint(100, 200));
	h.addPoint(BGPoint(200, 300));
	h.addPoint(BGPoint(300, 300));
	h.addPoint(BGPoint(500, 100));
	h.addPoint(BGPoint(300, 50));
	h.addPoint(BGPoint(100, 100));
	h.autoFinish();
	//h.delPoint();
	h.movePoint(BGPoint(200, 200), 1);
	h.movePoint(BGPoint(200, 100), 2);
	h.movePoint(BGPoint(200, 50));
	h.movePoint(BGPoint(100, 100), 0);
	h.moveY(20);
	h.moveX(30, 0);
	h.moveY(100, 0);
	h.addPoint();
	h.insertPoint(2);
	h.insertPoint(BGPoint(300, 400), 4);

	sf::RenderWindow window(sf::VideoMode(800, 600), "BGHitbox testing window");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);

		h.draw(CURRENT_POINT + POINTS + HITBOX_CONTENT + LINES + NUMBERS, window);

		window.display();

	}
	return 0;
}
