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
	unsigned char m_linesThickness;
	sf::Color m_linesColor;

	std::vector < sf::CircleShape > m_pointsToDraw;
	unsigned char m_pointsRadius;
	sf::Color m_pointsColor;

	std::vector < sf::VertexArray > m_content;
	sf::Color m_contentColor;

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
	void changeDrawableLine(unsigned char, unsigned char, unsigned char); //Change une ligne (avec son indice de premier paramètre) en utilisant la position de 2 points récupérables à partir de leurs indices dans la hitbox
	void readaptHitboxContent();

	//Pas besoin d'avoir des pointeurs pour les sf::Drawable pour réaliser une collection hétérogène, on passe directement par la méthode draw()

public:
	BGHitbox(	unsigned char = 3, sf::Color = sf::Color(255, 0, 0), unsigned char = 4, sf::Color = sf::Color(0, 255, 0),
		 		sf::Color = sf::Color(0, 0, 255), sf::Color = sf::Color(255, 255, 255), std::string = "arial.ttf",
				unsigned char = 14, sf::Color = sf::Color(128, 128, 128));
	~BGHitbox();

	//Setters & getters
	void setLinesThickness(unsigned char);
	unsigned char getLinesThickness() const;
	void setLinesColor(const sf::Color&);
	const sf::Color& getLinesColor() const;
	void setPointsRadius(unsigned char);
	unsigned char getPointsRadius() const;
	void setPointsColor(const sf::Color&);
	const sf::Color& getPointsColor() const;
	void setContentColor(const sf::Color&);
	const sf::Color& getContentColor() const;
	void setCurrentPointColor(const sf::Color&);
	const sf::Color& getCurrentPointColor() const;
	char getCurrentPoint() const; //Renvoie l'indice du point "courant"
	void setCurrentPoint(unsigned char);
	unsigned char size() const;

	//Interactions avec les hitbox
	void addPoint(const BGPoint&); //Ajoute un nouveau point à la hitbox (si cela est possible)
	void addPoint(); //Ajoute un point (il sera inséré au milieu du dernier segment) --> Appelle la méthode au-dessus
	void delPoint(char = -1); //Par défaut, cela supprimera le dernier point, sinon, utilise l'indice donné en paramètre (si c'est possible)
	void insertPoint(const BGPoint&, char = -1); //Pour insérer un point à un indice donné (si cela est possible). Insérer à l'indice -1 revient tout simplement à ajouter ce point à la fin --> addPoint() sera alors appellée
	void insertPoint(char = -1); //Pour insérer un point à un indice donné (il sera inséré au milieu du segment  des points adjacents) --> Appelle la méthode au-dessus
	void autoFinish(); //Pour terminer la hitbox automatiquement (si cela est possible) --> Relie le premier point au dernier
	void movePoint(const BGPoint&, char = -1); //Change la position d'un point à partir de son indice et de sa potientielle nouvelle position. L'indice -1 correspond au dernier point de la hitbox
	void moveX(unsigned int, char = -1); //Change la position d'un point seulement par rapport à sa position x et de son indice --> Appelle la méthode movePoint()
	void moveY(unsigned int, char = -1); //Change la position d'un point seulement par rapport à sa position y et de son indice --> Appelle la méthode movePoint()

	const BGPoint& getPoint(char = -1) const; //Renvoie un BGPoint en utilisant l'indice
	char getPoint(const BGPoint&) const; //Renvoie l'index d'un point de la hitbox s'il correspond au point envoyé en paramètre. Renvoie -1 si aucun point de la hitbox ne correspond
	char getPoint(unsigned int, unsigned int) const; //Renvoie l'index d'un point de la hitbox à partir de coordoonées (renvoie -1 si jamais les coordonnées ne correspondent à aucun point de la hitbox) --> appelle la méthode juste au-dessus

	void draw(char, sf::RenderWindow&); //Le premier paramètre utilise l'énumération WhatToDraw pour afficher les différents éléments sur le sf::RenderWindow envoyé en paramètre

};
#endif
