#include "BGHitbox.h"
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

const unsigned char BGHitbox::addRadiusCurrentPoint = 2;


void BGHitbox::addNewDrawablePoint(const BGPoint& _point, char _index)
{
	sf::CircleShape newPoint(m_pointRadius);
	newPoint.setFillColor(m_pointsColor);
	newPoint.setPosition(_point.x() - m_pointRadius, _point.y() - m_pointRadius);

	if (_index == -1)
	{
		m_pointsToDraw.push_back(newPoint);
	}
	else
	{
		m_pointsToDraw.insert(m_pointsToDraw.begin() + _index, newPoint);
	}
}

void BGHitbox::addNewDrawableLine(const BGSegment& _segment, char _index)
{
	sf::ConvexShape convex(4);
	convex.setOutlineThickness(m_thicknessLines);
	convex.setOutlineColor(m_linesColor);

	convex.setPoint(0, sf::Vector2f(_segment.P1().x(), _segment.P1().y()));
	convex.setPoint(1, sf::Vector2f(_segment.P2().x(), _segment.P2().y()));
	convex.setPoint(2, sf::Vector2f(_segment.P2().x(), _segment.P2().y()));
	convex.setPoint(3, sf::Vector2f(_segment.P1().x(), _segment.P1().y()));
	if (_index == -1)
	{
		m_linesToDraw.push_back(convex);
	}
	else
	{
		m_linesToDraw.insert(m_linesToDraw.begin() + _index, convex);
	}
}

void BGHitbox::readaptHitboxContent()
{
	std::vector < BGTriangle > triangles = m_hitbox.triangulate();
	m_hitboxContent.clear();
	for (unsigned char i = 0; i < triangles.size(); i++)
	{
  		sf::VertexArray tempTriangle(sf::Triangles, 3);
  		tempTriangle[0].position = sf::Vector2f(triangles[i].P1().x(), triangles[i].P1().y());
  		tempTriangle[1].position = sf::Vector2f(triangles[i].P2().x(), triangles[i].P2().y());
  		tempTriangle[2].position = sf::Vector2f(triangles[i].P3().x(), triangles[i].P3().y());
  		m_hitboxContent.push_back(tempTriangle);
	}
}

BGHitbox::BGHitbox()
{
	BGPolygon m_hitbox();

	m_thicknessLines = 3;
	m_linesColor = sf::Color(255, 0, 0);

	m_pointRadius = 4;
	m_pointsColor = sf::Color(0, 255, 0);

	m_indexCurrentPoint = -1;
	m_currentPointColor = sf::Color(0, 0, 255);
	m_currentPoint = sf::CircleShape(m_pointRadius + BGHitbox::addRadiusCurrentPoint);
	m_currentPoint.setFillColor(m_currentPointColor);

	m_hitboxContentColor = sf::Color(255, 255, 255);

	m_font = new sf::Font();
	if(!m_font->loadFromFile("arial.ttf"))//Passer par BGDataManager par la suite
	{
		std::cout << "Unable to open the font!" << std::endl;
	}
	m_fontSize = 14;
	m_fontColor = sf::Color(0, 0, 255);
}

BGHitbox::~BGHitbox()
{
	delete m_font; //Un problème si jamais la police n'a pas réussi à être chargée ? :thinking:
}

char BGHitbox::getCurrentPoint() const
{
	return m_indexCurrentPoint;
}

void BGHitbox::autoFinish()
{
	if (m_hitbox.autoFinish())
	{
		addNewDrawableLine(BGSegment(m_hitbox.getPoint(0), m_hitbox.getPoint(m_hitbox.size() - 1)));
		m_indexCurrentPoint = 0;
		m_currentPoint.setPosition(m_hitbox.getPoint(m_indexCurrentPoint).x() - (m_pointRadius + BGHitbox::addRadiusCurrentPoint), m_hitbox.getPoint(m_indexCurrentPoint).y() - (m_pointRadius + BGHitbox::addRadiusCurrentPoint));
		readaptHitboxContent();
	}
}

void BGHitbox::addPoint(const BGPoint& _point)
{
	if(m_hitbox.addPoint(_point)) //Si l'ajout du point a bien été réalisé
	{
		if (m_hitbox.isFinished()) //Si la hitbox est maintenant terminée
		{
			addNewDrawableLine(BGSegment(m_hitbox.getPoint(0), m_hitbox.getPoint(m_hitbox.size() - 2)));
			m_indexCurrentPoint = 0;
			m_currentPoint.setPosition(m_hitbox.getPoint(m_indexCurrentPoint).x() - (m_pointRadius + BGHitbox::addRadiusCurrentPoint), m_hitbox.getPoint(m_indexCurrentPoint).y() - (m_pointRadius + BGHitbox::addRadiusCurrentPoint));
		}
		else
		{
			addNewDrawablePoint(_point);
			m_indexCurrentPoint = m_hitbox.size() - 1;
			m_currentPoint.setPosition(m_hitbox.getPoint(m_indexCurrentPoint).x() - (m_pointRadius + BGHitbox::addRadiusCurrentPoint), m_hitbox.getPoint(m_indexCurrentPoint).y() - (m_pointRadius + BGHitbox::addRadiusCurrentPoint));
			sf::Text newNumber;
			newNumber.setFont(*m_font);
			newNumber.setString("lol");
			newNumber.setCharacterSize(m_fontSize);
			newNumber.setFillColor(m_fontColor);
			newNumber.setPosition(sf::Vector2f(100, 100));
			m_pointsNumbers.push_back(newNumber);
			if (m_hitbox.size() > 1)
			{
				addNewDrawableLine(BGSegment(_point, m_hitbox.getPoint(m_hitbox.size() - 2)));
				if (m_hitbox.size() >= 3)
				{
					readaptHitboxContent();
				}
			}
		}
	}
}

void BGHitbox::delPoint(char _index)
{
	bool wasFinished = m_hitbox.isFinished();
	if (m_hitbox.delPoint(_index))
	{
		if (m_hitbox.isFinished() != wasFinished) //Dans le cas où l'on a simplement arrêté la fin de la hitbox
		{
			m_linesToDraw.erase(m_linesToDraw.end() - 1);
		}
		else
		{
			m_linesToDraw.erase(m_linesToDraw.begin() + _index - 1);
			m_linesToDraw.erase(m_linesToDraw.begin() + _index - 1);
			m_pointsToDraw.erase(m_pointsToDraw.begin() + _index);
			addNewDrawableLine(BGSegment(m_hitbox.getPoint(_index - 1), m_hitbox.getPoint(_index)));
			readaptHitboxContent();
		}
	}
}

void BGHitbox::insertPoint(const BGPoint& _point, char _index)
{
	if (m_hitbox.insertPoint(_point, _index))
	{
		addNewDrawablePoint(_point, _index);
		unsigned char tempIndex;
		if (_index == -1)
		{
			addNewDrawableLine(BGSegment(_point, m_hitbox.getPoint(m_hitbox.size() - 2)));
		}
		else if (_index == 0)
		{
			addNewDrawableLine(BGSegment(_point, m_hitbox.getPoint(1)));
		}
		else
		{
			if (_index == 0)
			{
				tempIndex = m_hitbox.size() - 1;
			}
			else if (_index == m_hitbox.size() - 1)
			{
				tempIndex = _index - 2;
			}
			else
			{
				tempIndex = _index - 1;
			}
			m_linesToDraw.erase(m_linesToDraw.begin() + tempIndex);
			addNewDrawableLine(BGSegment(_point, m_hitbox.getPoint(tempIndex)), tempIndex);
			if (_index == m_hitbox.size() - 1)
			{
				tempIndex = 0;
			}
			else
			{
				tempIndex = _index + 1;
			}
			addNewDrawableLine(BGSegment(_point, m_hitbox.getPoint(tempIndex)), _index);
		}
		if (_index == -1) m_indexCurrentPoint = m_hitbox.size() - 1;
		else m_indexCurrentPoint = _index;
		m_currentPoint.setPosition(m_hitbox.getPoint(m_indexCurrentPoint).x() - (m_pointRadius + BGHitbox::addRadiusCurrentPoint), m_hitbox.getPoint(m_indexCurrentPoint).y() - (m_pointRadius + BGHitbox::addRadiusCurrentPoint));
		readaptHitboxContent();
	}
}

void BGHitbox::movePoint(const BGPoint& _point, char _index)
{
	if (m_hitbox.movePoint(_point, _index))
	{
		if (_index == -1) _index = m_hitbox.size() - 1;
		if (m_hitbox.size() >= 3)
		{
			if (_index == 0)
			{
				m_linesToDraw[0].setPoint(0, sf::Vector2f(_point.x(), _point.y()));
				m_linesToDraw[0].setPoint(1, sf::Vector2f(m_hitbox.getPoint(1).x(), m_hitbox.getPoint(1).y()));
				m_linesToDraw[0].setPoint(2, sf::Vector2f(m_hitbox.getPoint(1).x(), m_hitbox.getPoint(1).y()));
				m_linesToDraw[0].setPoint(3, sf::Vector2f(_point.x(), _point.y()));
			}
			else if (_index == m_hitbox.size() - 1)
			{
				m_linesToDraw[m_linesToDraw.size() - 1].setPoint(0, sf::Vector2f(_point.x(), _point.y()));
				m_linesToDraw[m_linesToDraw.size() - 1].setPoint(1, sf::Vector2f(m_hitbox.getPoint(_index - 1).x(), m_hitbox.getPoint(_index - 1).y()));
				m_linesToDraw[m_linesToDraw.size() - 1].setPoint(2, sf::Vector2f(m_hitbox.getPoint(_index - 1).x(), m_hitbox.getPoint(_index - 1).y()));
				m_linesToDraw[m_linesToDraw.size() - 1].setPoint(3, sf::Vector2f(_point.x(), _point.y()));
			}
			else
			{
				m_linesToDraw[_index - 1].setPoint(0, sf::Vector2f(_point.x(), _point.y()));
				m_linesToDraw[_index - 1].setPoint(1, sf::Vector2f(m_hitbox.getPoint(_index - 1).x(), m_hitbox.getPoint(_index - 1).y()));
				m_linesToDraw[_index - 1].setPoint(2, sf::Vector2f(m_hitbox.getPoint(_index - 1).x(), m_hitbox.getPoint(_index - 1).y()));
				m_linesToDraw[_index - 1].setPoint(3, sf::Vector2f(_point.x(), _point.y()));

				m_linesToDraw[_index].setPoint(0, sf::Vector2f(_point.x(), _point.y()));
				m_linesToDraw[_index].setPoint(1, sf::Vector2f(m_hitbox.getPoint(_index + 1).x(), m_hitbox.getPoint(_index + 1).y()));
				m_linesToDraw[_index].setPoint(2, sf::Vector2f(m_hitbox.getPoint(_index + 1).x(), m_hitbox.getPoint(_index + 1).y()));
				m_linesToDraw[_index].setPoint(3, sf::Vector2f(_point.x(), _point.y()));

			}
			m_pointsToDraw[_index].setPosition(sf::Vector2f(_point.x() - m_pointRadius, _point.y() - m_pointRadius));

			m_indexCurrentPoint = _index;
			m_currentPoint.setPosition(m_hitbox.getPoint(m_indexCurrentPoint).x() - (m_pointRadius + BGHitbox::addRadiusCurrentPoint), m_hitbox.getPoint(m_indexCurrentPoint).y() - (m_pointRadius + BGHitbox::addRadiusCurrentPoint));

			readaptHitboxContent();
		}
		else
		{
			unsigned char i = _index == 0;
			m_linesToDraw[0].setPoint(0, sf::Vector2f(_point.x(), _point.y()));
			m_linesToDraw[0].setPoint(1, sf::Vector2f(m_hitbox.getPoint(i).x(), m_hitbox.getPoint(i).y()));
			m_linesToDraw[0].setPoint(2, sf::Vector2f(m_hitbox.getPoint(i).x(), m_hitbox.getPoint(i).y()));
			m_linesToDraw[0].setPoint(3, sf::Vector2f(_point.x(), _point.y()));
		}
	}
}



void BGHitbox::draw(char _objectsToDraw, sf::RenderWindow& _window)
{

	if ((_objectsToDraw & 0x1) == 1) //Hitbox content
	{
		for (unsigned char i = 0; i < m_hitboxContent.size(); i++)
		{
			_window.draw(m_hitboxContent[i]);
		}
	}

	if ((_objectsToDraw & 0x2) == 2) //Lines
	{
		for (unsigned char i = 0; i < m_linesToDraw.size(); i++)
		{
			_window.draw(m_linesToDraw[i]);
		}
	}

	if ((_objectsToDraw & 0x4) == 4) //Points
	{
		for (unsigned char i = 0; i < m_pointsToDraw.size(); i++)
		{
			_window.draw(m_pointsToDraw[i]);
		}
	}

	if ((_objectsToDraw & 0x8) == 8) //Current point
	{
		if (m_indexCurrentPoint != -1)
		{
			_window.draw(m_currentPoint);
		}
	}

	if ((_objectsToDraw & 0x10) == 16) //Numbers
	{
		for (unsigned char i = 0; i < m_pointsNumbers.size(); i++)
		{
			_window.draw(m_pointsNumbers[i]);
		}
	}
}
