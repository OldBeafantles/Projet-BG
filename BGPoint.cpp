#include "BGPoint.h"
#include "BGSegment.h"
#include "BGHitbox.h"
#include "BGException.h"
#include <iostream>


BGPoint::BGPoint()
{
    m_x = 0;
    m_y = 0;
}

BGPoint::BGPoint(unsigned int _x, unsigned int _y)
{
    m_x = _x;
    m_y = _y;
}

unsigned int BGPoint::x() const
{
    return m_x;
}

unsigned int BGPoint::y() const
{
    return m_y;
}

void BGPoint::x(unsigned int _x)
{
    m_x = _x;
}

void BGPoint::y(unsigned int _y)
{
    m_y = _y;
}

double BGPoint::getCoeff(const BGPoint& _p) const
{
    return ((double)(_p.y()) - (double)(m_y)) / ((double)(_p.x()) - (double)(m_x));
}

double BGPoint::getCoeff(const BGPoint& _p1, const BGPoint& _p2)
{
    return ((double)(_p2.y()) - (double)(_p1.y())) / ((double)(_p2.x()) - (double)(_p1.x()));
}

bool BGPoint::areVertical(const BGPoint& _p1, const BGPoint& _p2)
{
    return BGSegment(_p1, _p2).isVertical();
}

bool BGPoint::isDifferent(const BGPoint& _p) const
{
    return !(m_x == _p.x() && m_y == _p.y());
}

bool BGPoint::areDifferent(const BGPoint& _p1, const BGPoint& _p2)
{
    return _p1.isDifferent(_p2);
}

int BGPoint::getEquationValue(const BGPoint& _P0, const BGPoint& _P1, const BGPoint& _M)
{
	return (_M.x() - _P1.x()) * (_P0.y() - _P1.y()) - (_P0.x() - _P1.x()) * (_M.y() - _P1.y());
}

bool BGPoint::isInTriangle(const BGTriangle& _triangle, const BGPoint& _point)
//http://i.imgur.com/0lXdSNO.png
{
    bool b1, b2, b3;
    b1 = BGPoint::getEquationValue(_triangle.P1(), _triangle.P2(), _point) < 0;
    b2 = BGPoint::getEquationValue(_triangle.P2(), _triangle.P3(), _point) < 0;
    b3 = BGPoint::getEquationValue(_triangle.P3(), _triangle.P1(), _point) < 0;

    return (b1 == b2) && (b2 == b3);
}

bool BGPoint::areAligned(const BGPoint& _p1, const BGPoint& _p2, const BGPoint& _p3)
{
    double temp1 = (_p2.y() - _p1.y()) / (_p2.x() - _p1.x());
    double temp2 = (_p3.y() - _p1.y()) / (_p3.x() - _p1.x());
    return temp1 == temp2;
}

unsigned int BGPoint::operator[] (char _index)
{
    switch (_index)
    {
        case 0: return m_x;
        case 1: return m_y;
        default:
            std::cout << "Erreur : Index non compris entre 0 et 1 inclus !" << std::endl;
            throw BGException(2, "L'indice est incorrect, il doit être égal à 0 ou 1");
            break;
    }
}
