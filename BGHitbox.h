#ifndef BG_HITBOX_H
#define BG_HITBOX_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "BGSegment.h"
#include "BGPoint.h"
#include "BGTriangle.h"
#include "BGPolygon.h"

enum WhatToDraw
{
	HITBOX_CONTENT = 1,
	LINES = 2,
	POINTS = 4,
	CURRENT_POINT = 8,
	NUMBERS = 16
};


class BGHitbox
{
private:

	BGPolygon m_hitbox;

	std::vector < sf::ConvexShape > m_linesToDraw;
	unsigned char m_thicknessLines;
	sf::Color m_linesColor;

	std::vector < sf::CircleShape > m_pointsToDraw;
	unsigned char m_pointRadius;
	sf::Color m_pointsColor;

	std::vector < sf::VertexArray > m_hitboxContent;
	sf::Color m_hitboxContentColor;

	sf::CircleShape m_currentPoint;
	char m_indexCurrentPoint; //est égal à -1 à la création d'une nouvelle hitbox
	sf::Color m_currentPointColor;

	sf::Font* m_font; //Un pointeur car on va passer par BGDataManager quand il sera fait
	unsigned char m_fontSize;
	sf::Color m_fontColor;
	std::vector < sf::Text > m_pointsNumbers;

	static const unsigned char addRadiusCurrentPoint;

	//Méthodes private car utilisées dans celles "publiques"
	void addNewDrawablePoint(const BGPoint&, char = -1); //Si l'indice vaut -1, la rajoute à la fin du vector
	void addNewDrawableLine(const BGSegment&, char = -1); //Si l'indice vaut -1, la rajoute à la fin du vector
	void readaptHitboxContent();

	//Pas besoin d'avoir des pointeurs pour les sf::Drawable pour réaliser une collection hétérogène, on passe directement par la méthode draw()

public:
	BGHitbox();
	~BGHitbox();
	void addPoint(const BGPoint&); //Ajouter un nouveau point à la hitbox (si cela est possible)
	void delPoint(char = -1); //Par défaut, cela supprimera le dernier point, sinon, utilise l'indice donné en paramètre (si c'est possible)
	void insertPoint(const BGPoint&, char = -1); //Pour insérer un point à un indice donné (si cela est possible)
	void autoFinish(); //Pour terminer la hitbox automatiquement (si cela est possible)
	void movePoint(const BGPoint&, char = -1); //Change la position d'un point à partir de son indice et de sa potientielle nouvelle position

	void draw(char, sf::RenderWindow&);
	char getCurrentPoint() const; //Renvoie l'indice du point "courant"

};
#endif
