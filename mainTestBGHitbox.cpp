#include "BGHitbox.h"
#include <SFML/Graphics.hpp>

int main()
{
	//Quelques tests pour vérifier que je n'ai pas fait d'erreurs

	BGHitbox h;

	h.addPoint(20, 20);
	h.addPoint(500, 20);
	h.addPoint(500, 500);
	h.addPoint(20, 500);
	h.autoFinish();

	//h.addPoint(1, 1);
	//h.addPoint(4, -1);
	//h.addPoint(3, -3);
	//h.addPoint(1, 0);
	//h.addPoint(-1, -3);
	//h.addPoint(-2, -1);
	//h.autoFinish();
	//h.insertPoint(3, 3, 1);
	//h.insertPoint(3, 1, -2);
	//h.delPoint(1);
	//h.delPoint(2);


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

		window.draw(h.showHitboxContent());

		auto lines = h.showLines();
		for (unsigned char i = 0; i < lines.size(); i++)
		{
			window.draw(lines[i]);
		}

		auto points = h.showPoints();
		for (unsigned char i = 0; i < points.size(); i++)
		{
			window.draw(points[i]);
		}

		window.display();
	}
	return 0;
}