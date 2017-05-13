#include "BGHitbox.h"
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

const unsigned char BGHitbox::addRadiusCurrentPoint = 2;


void BGHitbox::addNewDrawablePoint(const BGPoint& _point, char _index)
{
	sf::CircleShape newPoint(m_pointsRadius);
	newPoint.setFillColor(m_pointsColor);
	newPoint.setPosition(_point.x() - m_pointsRadius, _point.y() - m_pointsRadius);

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
	convex.setOutlineThickness(m_linesThickness);
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
	m_content.clear();
	for (unsigned char i = 0; i < triangles.size(); i++)
	{
  		sf::VertexArray tempTriangle(sf::Triangles, 3);
  		tempTriangle[0].position = sf::Vector2f(triangles[i].P1().x(), triangles[i].P1().y());
  		tempTriangle[1].position = sf::Vector2f(triangles[i].P2().x(), triangles[i].P2().y());
  		tempTriangle[2].position = sf::Vector2f(triangles[i].P3().x(), triangles[i].P3().y());
  		m_content.push_back(tempTriangle);
	}
}

BGHitbox::BGHitbox(	unsigned char _thicknessLines, sf::Color _linesColor, unsigned char _pointsRadius, sf::Color _pointsColor,
	 				sf::Color _currentPointColor, sf::Color _contentColor, std::string _fontPath, unsigned char _fontSize,
					sf::Color _fontColor)
{
	BGPolygon m_hitbox();

	m_linesThickness = _thicknessLines;
	m_linesColor = _linesColor;

	m_pointsRadius = _pointsRadius;
	m_pointsColor = _pointsColor;

	m_indexCurrentPoint = -1;
	m_currentPointColor = _currentPointColor;
	m_currentPoint = sf::CircleShape(m_pointsRadius + BGHitbox::addRadiusCurrentPoint);
	m_currentPoint.setFillColor(m_currentPointColor);

	m_contentColor = _contentColor;

	m_font = new sf::Font();
	if(!m_font->loadFromFile(_fontPath))//Passer par BGDataManager par la suite
	{
		std::cout << "Unable to open the font!" << std::endl;
	}
	m_fontSize = _fontSize;
	m_fontColor = _fontColor;
}

BGHitbox::~BGHitbox()
{
	delete m_font; //Un problème si jamais la police n'a pas réussi à être chargée ? :thinking:
}

void BGHitbox::setLinesThickness(unsigned char _thickness)
{
	if (_thickness <= 30 && _thickness != 0)
	{
		m_linesThickness = _thickness;
		for (unsigned char i = 0; i < m_linesToDraw.size(); i++)
		{
			m_linesToDraw[i].setOutlineThickness(_thickness);
		}
	}
	else
	{
		std::cout << "Veuillez choisir une épaisseur moins élevée !" << std::endl;
	}
}

unsigned char BGHitbox::getLinesThickness() const
{
	return m_linesThickness;
}

const sf::Color& BGHitbox::getLinesColor() const
{
	return m_linesColor;
}

void BGHitbox::setLinesColor(const sf::Color& _color)
{
	m_linesColor = _color;
	for (unsigned char i = 0; i < m_linesToDraw.size(); i++)
	{
		m_linesToDraw[i].setOutlineColor(_color);
	}
}

void BGHitbox::setPointsRadius(unsigned char _radius)
{
	if (_radius <= 30 && _radius != 0)
	{
		char diff = m_pointsRadius - _radius;
		for (unsigned char i = 0; i < m_pointsToDraw.size(); i++)
		{
			m_pointsToDraw[i].setRadius(_radius);
			m_pointsToDraw[i].setPosition(sf::Vector2f(m_pointsToDraw[i].getPosition().x + diff, m_pointsToDraw[i].getPosition().y + diff));
		}
		m_currentPoint.setRadius(_radius + BGHitbox::addRadiusCurrentPoint);
		m_currentPoint.setPosition(sf::Vector2f(m_currentPoint.getPosition().x + diff, m_currentPoint.getPosition().y + diff));
		m_pointsRadius = _radius;
	}
	else
	{
		std::cout << "Veuillez choisir une valeur correcte !" << std::endl;
	}
}

unsigned char BGHitbox::getPointsRadius() const
{
	return m_pointsRadius;
}

void BGHitbox::setPointsColor(const sf::Color& _color)
{
	for (unsigned char i = 0; i < m_pointsToDraw.size(); i++)
	{
		m_pointsToDraw[i].setFillColor(_color);
	}
}

const sf::Color& BGHitbox::getPointsColor() const
{
	return m_pointsColor;
}

void BGHitbox::setContentColor(const sf::Color& _color)
{
	m_contentColor = _color;
	for (unsigned char i = 0; i < m_content.size(); i++)
	{
		m_content[i][0].color = _color;
		m_content[i][1].color = _color;
		m_content[i][2].color = _color;
	}
}

const sf::Color& BGHitbox::getContentColor() const
{
	return m_contentColor;
}

void BGHitbox::setCurrentPointColor(const sf::Color& _color)
{
	m_currentPoint.setFillColor(_color);
}

const sf::Color& BGHitbox::getCurrentPointColor() const
{
	return m_currentPointColor;
}

char BGHitbox::getCurrentPoint() const
{
	return m_indexCurrentPoint;
}

char BGHitbox::getPoint(const BGPoint& _point) const
{
	unsigned int x, y;
	for (char i = m_hitbox.size() - 1; i >= 0; i--)
	{
		x = m_hitbox.getPoint(i).x();
		y = m_hitbox.getPoint(i).y();
		if (_point.x() >= x - m_pointsRadius && _point.x() <= x + m_pointsRadius && _point.y() >= y - m_pointsRadius && _point.y() <= y + m_pointsRadius)
		{
			return i;
		}
	}
	return -1;
}

char BGHitbox::getPoint(unsigned int _x, unsigned _y) const
{
	return getPoint(BGPoint(_x, _y));
}

void BGHitbox::autoFinish()
{
	if (m_hitbox.autoFinish())
	{
		addNewDrawableLine(BGSegment(m_hitbox.getPoint(0), m_hitbox.getPoint(m_hitbox.size() - 1)));
		m_indexCurrentPoint = 0;
		m_currentPoint.setPosition(m_hitbox.getPoint(m_indexCurrentPoint).x() - (m_pointsRadius + BGHitbox::addRadiusCurrentPoint), m_hitbox.getPoint(m_indexCurrentPoint).y() - (m_pointsRadius + BGHitbox::addRadiusCurrentPoint));
		readaptHitboxContent();
	}
}

void BGHitbox::addPoint(const BGPoint& _point)
{
	bool wasFinished = m_hitbox.isFinished();
	if(m_hitbox.addPoint(_point)) //Si l'ajout du point a bien été réalisé
	{
		if (wasFinished)
		{
			m_linesToDraw.erase(m_linesToDraw.end() - 1);
			addNewDrawableLine(BGSegment(m_hitbox.getPoint(m_hitbox.size() - 2), m_hitbox.getPoint(m_hitbox.size() - 1)));
			addNewDrawableLine(BGSegment(m_hitbox.getPoint(m_hitbox.size() - 1), m_hitbox.getPoint(0)));
			m_indexCurrentPoint = m_hitbox.size() - 1;
			m_currentPoint.setPosition(m_hitbox.getPoint(m_indexCurrentPoint).x() - (m_pointsRadius + BGHitbox::addRadiusCurrentPoint), m_hitbox.getPoint(m_indexCurrentPoint).y() - (m_pointsRadius + BGHitbox::addRadiusCurrentPoint));
			addNewDrawablePoint(_point);
		}
		else if (m_hitbox.isFinished()) //Si la hitbox est maintenant terminée
		{
			addNewDrawableLine(BGSegment(m_hitbox.getPoint(0), m_hitbox.getPoint(m_hitbox.size() - 2)));
			m_indexCurrentPoint = 0;
			m_currentPoint.setPosition(m_hitbox.getPoint(m_indexCurrentPoint).x() - (m_pointsRadius + BGHitbox::addRadiusCurrentPoint), m_hitbox.getPoint(m_indexCurrentPoint).y() - (m_pointsRadius + BGHitbox::addRadiusCurrentPoint));
		}
		else
		{
			addNewDrawablePoint(_point);
			m_indexCurrentPoint = m_hitbox.size() - 1;
			m_currentPoint.setPosition(m_hitbox.getPoint(m_indexCurrentPoint).x() - (m_pointsRadius + BGHitbox::addRadiusCurrentPoint), m_hitbox.getPoint(m_indexCurrentPoint).y() - (m_pointsRadius + BGHitbox::addRadiusCurrentPoint));
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

void BGHitbox::addPoint()
{
	BGPoint point = BGSegment::getMiddle(BGSegment(m_hitbox.getPoint(0), m_hitbox.getPoint(m_hitbox.size() - 1)));
	addPoint(point);
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
		m_currentPoint.setPosition(m_hitbox.getPoint(m_indexCurrentPoint).x() - (m_pointsRadius + BGHitbox::addRadiusCurrentPoint), m_hitbox.getPoint(m_indexCurrentPoint).y() - (m_pointsRadius + BGHitbox::addRadiusCurrentPoint));
		readaptHitboxContent();
	}
}

void BGHitbox::insertPoint(char _index)
{
	BGPoint point;
	if (_index == 0 || _index == -1 || _index == m_hitbox.size() - 1)
	{
		point = BGSegment::getMiddle(BGSegment(m_hitbox.getPoint(0), m_hitbox.getPoint(m_hitbox.size() - 1)));
	}
	else
	{
		point = BGSegment::getMiddle(BGSegment(m_hitbox.getPoint(_index), m_hitbox.getPoint(_index - 1)));
	}

	if (_index == -1 || _index == m_hitbox.size() - 1)
	{
		addPoint(point);
	}
	else
	{
		insertPoint(point, _index);
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
				if (m_hitbox.isFinished())
				{
					m_linesToDraw[m_linesToDraw.size() - 1].setPoint(0, sf::Vector2f(_point.x(), _point.y()));
					m_linesToDraw[m_linesToDraw.size() - 1].setPoint(1, sf::Vector2f(m_hitbox.getPoint(m_hitbox.size() - 1).x(), m_hitbox.getPoint(m_hitbox.size() - 1).y()));
					m_linesToDraw[m_linesToDraw.size() - 1].setPoint(2, sf::Vector2f(m_hitbox.getPoint(m_hitbox.size() - 1).x(), m_hitbox.getPoint(m_hitbox.size() - 1).y()));
					m_linesToDraw[m_linesToDraw.size() - 1].setPoint(3, sf::Vector2f(_point.x(), _point.y()));
				}
			}
			else if (_index == m_hitbox.size() - 1)
			{
				m_linesToDraw[m_linesToDraw.size() - 2].setPoint(0, sf::Vector2f(_point.x(), _point.y()));
				m_linesToDraw[m_linesToDraw.size() - 2].setPoint(1, sf::Vector2f(m_hitbox.getPoint(m_hitbox.size() - 2).x(), m_hitbox.getPoint(m_hitbox.size() - 2).y()));
				m_linesToDraw[m_linesToDraw.size() - 2].setPoint(2, sf::Vector2f(m_hitbox.getPoint(m_hitbox.size() - 2).x(), m_hitbox.getPoint(m_hitbox.size() - 2).y()));
				m_linesToDraw[m_linesToDraw.size() - 2].setPoint(3, sf::Vector2f(_point.x(), _point.y()));
				if (m_hitbox.isFinished())
				{
					m_linesToDraw[m_linesToDraw.size() - 1].setPoint(0, sf::Vector2f(_point.x(), _point.y()));
					m_linesToDraw[m_linesToDraw.size() - 1].setPoint(1, sf::Vector2f(m_hitbox.getPoint(0).x(), m_hitbox.getPoint(0).y()));
					m_linesToDraw[m_linesToDraw.size() - 1].setPoint(2, sf::Vector2f(m_hitbox.getPoint(0).x(), m_hitbox.getPoint(0).y()));
					m_linesToDraw[m_linesToDraw.size() - 1].setPoint(3, sf::Vector2f(_point.x(), _point.y()));
				}
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
			m_pointsToDraw[_index].setPosition(sf::Vector2f(_point.x() - m_pointsRadius, _point.y() - m_pointsRadius));

			m_indexCurrentPoint = _index;
			m_currentPoint.setPosition(m_hitbox.getPoint(m_indexCurrentPoint).x() - (m_pointsRadius + BGHitbox::addRadiusCurrentPoint), m_hitbox.getPoint(m_indexCurrentPoint).y() - (m_pointsRadius + BGHitbox::addRadiusCurrentPoint));

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

void BGHitbox::moveX(unsigned int _x, char _index)
{
	unsigned int y;
	if (_index == -1) y = m_hitbox.getPoint(m_hitbox.size() - 1).y();
	else y = m_hitbox.getPoint(_index).y();
	movePoint(BGPoint(_x, y), _index);
}

void BGHitbox::moveY(unsigned int _y, char _index)
{
	unsigned int x;
	if (_index == -1) x = m_hitbox.getPoint(m_hitbox.size() - 1).x();
	else x = m_hitbox.getPoint(_index).x();
	movePoint(BGPoint(x, _y), _index);
}

void BGHitbox::draw(char _objectsToDraw, sf::RenderWindow& _window)
{

	if ((_objectsToDraw & 0x1) == 1) //Hitbox content
	{
		for (unsigned char i = 0; i < m_content.size(); i++)
		{
			_window.draw(m_content[i]);
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
