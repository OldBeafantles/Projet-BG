#include "BGPolygon.h"
#include "BGSegment.h"
#include <iostream>

const unsigned char BGPolygon::m_nbMaxPoints = 100;


BGPolygon::BGPolygon()
{
    m_finished = false;
}


BGPoint BGPolygon::operator[] (char _index) const
{
    if (_index >= 0 && _index < m_points.size())
    {
        return m_points[_index];
    }
    else
    {
        std::cout << "Erreur : Index non compris entre 0 et 1 inclus !" << std::endl;
    }
}

BGPoint BGPolygon::getPoint(unsigned char _index) const
{
    return (*(this))[_index];
}

bool BGPolygon::isFinished() const
{
    return m_finished;
}

unsigned char BGPolygon::size() const
{
    return m_points.size();
}


bool BGPolygon::addPoint(const BGPoint& _point)
{
    if (!m_finished)
    {
        if (m_points.size() < m_nbMaxPoints)
        {
            if (m_points.size() < 3) //Dans le cas où il y a moins de 3 points, le nouveau segment potientiellement créé avec le point ne pourra pas être sécant avec les autres
            {
                m_points.push_back(_point);
                std::cout << "Point ajouté !" << std::endl;
                return true;
            }
            else
            {
                bool secant = false;
                unsigned char i = 0;
                while (i < m_points.size() - 2 && !secant) //Le nouveau segment potentiellement créé ne pourra dans tous les cas pas être sécant avec le segment formé par les deux derniers points, d'où le m_points.size() - 2
                {
                    secant = BGSegment::areSecant(BGSegment(_point, m_points[m_points.size() - 1]), BGSegment(m_points[i], m_points[i + 1]));
                    i++;
                }
                if (!secant) //S'il est égal au premier point, alors cela signifie qu'il "fermera" la hitbox
                {
                    if (_point.x() == m_points[0].x() && _point.y() == m_points[0].y())
                    {
                        m_finished = true;
                        std::cout << "Hitbox terminée !" << std::endl;
                        return true;
                    }
                    else
                    {
                        m_points.push_back(_point);
                        std::cout << "Point ajouté !" << std::endl;
                        return true;
                    }
                }
                else
                {
                    std::cout << "Impossible d'ajouter le point : Segments sécants !" << std::endl;
                    return false;
                }
            }
        }
        else
        {
            std::cout << "Nombre maximal de points atteint !" << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Impossible de rajouter un point alors que la hitbox est terminée. Si vous souhaitez le faire, supprimez d'abord le dernier point !" << std::endl;
        return false;
    }
}


bool BGPolygon::delPoint(char _index)
{
    if (_index == -1) _index = m_points.size() - 1;
    if (_index >= -1 && _index <= m_points.size() - 1)
	{
		if (m_finished && (_index == -1 || _index == m_points.size() - 1))
		{
			m_finished = false; //Dans le cas où la hitbox est "finie", supprimer le dernier point revient à considérer la hitbox comme non "fermée"

			std::cout << "Hitbox plus 'terminée'" << std::endl;
            return true;
		}
		else if (m_points.size() < 5) //Dans le cas où la hitbox a moins de 5 points, la supression de l'un d'eux ne pose aucun problème d'intersection avec le nouveau segment
		{
			m_points.erase(m_points.begin() + _index);
			std::cout << "Point supprimé !" << std::endl;
            return true;
		}
		else
		{
			if (_index == -1)
			{
				_index = m_points.size() - 1;
			}
			//Schéma pour comprendre les explications suivantes : http://i.imgur.com/kFT3MGb.png

			//On doit maintenant vérifier que la suppression de ce point n'entraîne pas de problèmes (segments sécants avec ce le nouveau segment créé <-- le rouge)
			bool secant = false;
			unsigned char i = 0;
			BGPoint p1, p2; //Les coordonnées des points du segment (le rouge) nouveau potientiellement créé par la potientelle supression du point

			if (_index == 0)
			{
                p1 = m_points[m_points.size() - 1];
			}
			else
			{
				p1 = m_points[_index - 1];
			}

			if (_index == m_points.size() - 1)
			{
				p2 = m_points[0];
			}
			else
			{
				p2 = m_points[_index + 1];
			}

			while (i < _index - 2 && !secant) //Dans tous les cas, cela ne sert à rien de tester si les segments adjacents à celui qui va être potentiellement créé sont sécants avec lui (les segments bleus ne pourront jamais être sécants avec le segment rouge)
			{
				secant = BGSegment::areSecant(BGSegment(p1, p2), BGSegment(m_points[i], m_points[i + 1]));
				i++;
			}
			if (!secant)
			{
				i = _index + 2;
				while (i < m_points.size() - 2 && !secant)
				{
					secant = BGSegment::areSecant(BGSegment(p1, p2), BGSegment(m_points[i], m_points[i + 1]));
					i++;
				}
				if (!secant)
				{
					m_points.erase(m_points.begin() + _index);
					std::cout << "Point supprimé !" << std::endl;
                    return true;
				}
				else
				{
					std::cout << "Impossible de supprimer ce point : segments sécants !" << std::endl;
                    return false;
				}
			}
			else
			{
				std::cout << "Impossible de supprimer ce point : segments sécants !" << std::endl;
                return false;
			}
		}
	}
	else
	{
		std::cout << "Indice incorrect..." << std::endl;
        return false;
	}
}

bool BGPolygon::insertPoint(const BGPoint& _point, char _index)
{
    if (_index == -1)
    {
        this->addPoint(_point);
    }
    else
    {
        if (_index >= -1 && _index <= m_points.size() - 1)
    	{
    		if (m_points.size() < m_nbMaxPoints)
    		{
    			//Voir schéma
    			unsigned char i = 0;
    			bool secant = false;
                BGSegment firstNewLine =BGSegment(_point, m_points[_index]);
                BGSegment secondNewLine;
                if (_index == 0)
                {
                    secondNewLine = BGSegment(_point, m_points[m_points.size() - 1]);
                }
                else
                {
                    secondNewLine = BGSegment(_point, m_points[_index - 1]);
                }

    			while (i < m_points.size() && !secant)
    			{
                    if (i != _index - 1 && i != _index)
                    {
                        if (i == _index - 2)
                        {
                            secant = BGSegment::areSecant(secondNewLine, BGSegment(m_points[i], m_points[i + 1]));
                        }
                        else if (i == _index + 1)
                        {
                            secant = BGSegment::areSecant(firstNewLine, BGSegment(m_points[i], m_points[i + 1]));
                        }
                        else if (i == m_points.size() - 1)
                        {
                            secant = BGSegment::areSecant(firstNewLine, BGSegment(m_points[0], m_points[m_points.size() - 1]));
                            if (!secant)
                            {
                                secant = BGSegment::areSecant(secondNewLine, BGSegment(m_points[0], m_points[m_points.size() - 1]));
                            }
                        }
                        else
                        {
                            secant = BGSegment::areSecant(firstNewLine, BGSegment(m_points[i], m_points[i + 1]));
                            if (!secant)
                            {
                                secant = BGSegment::areSecant(secondNewLine, BGSegment(m_points[i], m_points[i + 1]));
                            }
                        }
                    }
    				i++;
    			}
    			if (!secant)
    			{
                    m_points.insert(m_points.begin() + _index, _point);
					std::cout << "Point inséré !" << std::endl;
                    return true;
    			}
				else
				{
					std::cout << "Impossible : segments sécants !" << std::endl;
                    return false;
				}
    		}
    		else
    		{
    			std::cout << "Nombre maximal de points atteint !" << std::endl;
                return false;
    		}
    	}
    	else
    	{
    		std::cout << "Indice incorrect..." << std::endl;
            return false;
    	}
    }
}

bool BGPolygon::movePoint(const BGPoint& _point, char _index)
{
    if (_index == -1) _index = m_points.size() - 1;
    if (_index >= 0 && _index <= m_points.size() - 1)
    {
        if (m_points.size() >= 4)
        {
            unsigned char i = 0;
            bool secant = false;
            BGSegment firstNewLine;
            BGSegment secondNewLine;
            if (_index == 0)
            {
                firstNewLine = BGSegment(_point, m_points[m_points.size() - 1]);
                secondNewLine = BGSegment(_point, m_points[1]);
            }
            else if (_index == m_points.size() - 1)
            {
                firstNewLine = BGSegment(_point, m_points[_index - 1]);
                secondNewLine = BGSegment(_point, m_points[0]);
            }
            else
            {
                firstNewLine = BGSegment(_point, m_points[_index - 1]);
                secondNewLine = BGSegment(_point, m_points[_index + 1]);
            }

            while (i < m_points.size() && !secant)
            {
                if (i != _index - 1 && i != _index)
                {
                    if (i == _index - 2)
                    {
                        secant = BGSegment::areSecant(secondNewLine, BGSegment(m_points[i], m_points[i + 1]));
                    }
                    else if (i == _index + 1)
                    {
                        secant = BGSegment::areSecant(firstNewLine, BGSegment(m_points[i], m_points[i + 1]));
                    }
                    else if (i == m_points.size() - 1)
                    {
                        if (i == getNeighbourVertice(_index, -2))
                        {
                            secant = BGSegment::areSecant(secondNewLine, BGSegment(m_points[i], m_points[0]));
                        }
                        else
                        {
                            secant = BGSegment::areSecant(firstNewLine, BGSegment(m_points[0], m_points[m_points.size() - 1]));
                            if (!secant)
                            {
                                secant = BGSegment::areSecant(secondNewLine, BGSegment(m_points[0], m_points[m_points.size() - 1]));
                            }
                        }
                    }
                    else
                    {
                        if (i == getNeighbourVertice(_index, -2))
                        {
                            secant = BGSegment::areSecant(secondNewLine, BGSegment(m_points[i], m_points[0]));
                        }
                        else
                        {
                            secant = BGSegment::areSecant(firstNewLine, BGSegment(m_points[i], m_points[i + 1]));
                            if (!secant)
                            {
                                secant = BGSegment::areSecant(secondNewLine, BGSegment(m_points[i], m_points[i + 1]));
                            }
                        }
                    }
                }
                i++;
            }
            if (!secant)
            {
                m_points[_index].x(_point.x());
                m_points[_index].y(_point.y());
                std::cout << "Position changée !" << std::endl;
                return true;
            }
            else
            {
                std::cout << "Impossible : segments sécants !" << std::endl;
                return false;
            }
        }
        else
        {
            m_points[_index].x(_point.x());
            m_points[_index].y(_point.y());
            std::cout << "Position changée !" << std::endl;
            return true;
        }
    }
    else
    {
        std::cout << "Indice incorrect !" << std::endl;
        return false;
    }
}


bool BGPolygon::autoFinish()
{
    if (m_points.size() > 2)
    {
        BGSegment lastLine = BGSegment(m_points[0], m_points[m_points.size() - 1]);
        bool secant = false;
        unsigned char i = 1;
        while (i < m_points.size() - 3 && !secant)
        {
            secant = BGSegment::areSecant(lastLine, BGSegment(m_points[i], m_points[i + 1]));
            i++;
        }
        if (!secant)
        {
            m_finished = true;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

std::vector < BGTriangle > BGPolygon::triangulate() const //Ne peut être utilisé que pour les polygones de plus de 3 côtés
{
    std::vector < BGTriangle > triangles;
    BGPolygon polygon = *(this);
    if (polygon.size() > 2)
    {
        bool isEar = true, hasSomethingIn;

        unsigned char indexLeftVertice, c1,  c2, i;
        BGPoint p1, p2, p3;

        while (polygon.size() > 3)
        {
            if (isEar)
            {
                indexLeftVertice = polygon.getLeftVertice();
            }
            else
            {
                indexLeftVertice = polygon.getNeighbourVertice(indexLeftVertice, 1);
            }

            c1 = polygon.getNeighbourVertice(indexLeftVertice, -1);
            c2 = polygon.getNeighbourVertice(indexLeftVertice, 1);

            p1 = polygon[indexLeftVertice];
            p2 = polygon[c1];
            p3 = polygon[c2];

            hasSomethingIn = false;
            i = 0;
            while (i < polygon.size() && !hasSomethingIn)
            {
                if (i != indexLeftVertice && i != c1 && i != c2)
                {
                    hasSomethingIn = BGPoint::isInTriangle(BGTriangle(p1, p2, p3), polygon[i]);
                }
                i++;
            }
            if (!hasSomethingIn)
            {
                triangles.push_back(BGTriangle(p1, p2, p3));
                polygon.delPoint(indexLeftVertice);
                isEar = true;
            }
            else
            {
                isEar = false;
            }
        }
        triangles.push_back(BGTriangle(polygon[0], polygon[1], polygon[2]));
        return triangles;
    }
    else
    {
        return triangles;
    }
}

std::vector < BGTriangle > BGPolygon::triangulateAPolygon(BGPolygon* _polygon)
{
    return _polygon->triangulate();
}

unsigned char BGPolygon::getLeftVertice() const
{
	unsigned int x = m_points[0].x();
	unsigned char index = 0;
	for (unsigned char i = 1; i < m_points.size(); i++)
	{
		if (m_points[i].x() < x)
		{
			x = m_points[i].x();
			index = i;
		}
	}
	return index;
}

unsigned char BGPolygon::getNeighbourVertice(unsigned char _i, char _di) const
{
	return getNeighbourVertice(_i, _di, m_points.size());
}

unsigned char BGPolygon::getNeighbourVertice(unsigned char _i, char _di, unsigned char _size)
{
    char index = _i + _di;
    if (index >= 0)
	{
		return index % _size;
	}
	else
	{
		return index + _size;
	}
}
