#include "BGSegment.h"
#include "BGPoint.h"
#include "BGException.h"
#include <iostream>

BGSegment::BGSegment() : m_p1(BGPoint()), m_p2(BGPoint())
{}

BGSegment::BGSegment(const BGPoint& _p1, const BGPoint& _p2)
{
    m_p1 = _p1;
    m_p2 = _p2;
}

BGSegment::BGSegment(unsigned int _x1, unsigned int _y1, unsigned int _x2, unsigned int _y2) : m_p1(BGPoint(_x1, _y1)), m_p2(BGPoint(_x2, _y2))
{}

BGPoint BGSegment::P1() const
{
    return m_p1;
}

BGPoint BGSegment::P2() const
{
    return m_p2;
}

void BGSegment::P1(const BGPoint& _point)
{
    m_p1 = _point;
}

void BGSegment::P2(const BGPoint& _point)
{
    m_p2 = _point;
}

bool BGSegment::isVertical() const
{
    return m_p1.x() == m_p2.x();
}

double BGSegment::getCoeff() const
{
    return m_p2.getCoeff(m_p1);
}

double BGSegment::getIntercept() const
{
    return m_p1.y() - getCoeff() * m_p1.x();
}

bool BGSegment::isXIn(double _x, const BGSegment& _s)
{
    return (_x > _s.P1().x() && _x < _s.P2().x()) || (_x < _s.P1().x() && _x > _s.P2().x());
}

bool BGSegment::isXIn(double _x, unsigned int _x1, unsigned int _x2)
{
    return ((_x >= _x1 && _x <= _x2) || (_x <= _x1 && _x >= _x2));
}


bool BGSegment::isYIn(unsigned int _y, const BGSegment& _s)
{
    return (_y >= _s.P1().y() && _y <= _s.P2().y()) || (_y <= _s.P1().y() && _y >= _s.P2().y());
}

bool BGSegment::areSecant(const BGSegment& _s1, const BGSegment& _s2)
{
    if (_s1.isVertical() && _s2.isVertical())
    {
        return false;
    }
    if (_s1.isVertical() || _s2.isVertical()) //Dans le cas où au moins un des segments est vertical
    {

        //On récupère le segment vertical et le segment "normal"
        BGSegment sVertical, s;
        if (_s1.isVertical()) {sVertical = copySegment(_s1); s = copySegment(_s2);}
        else {s = copySegment(_s1); sVertical = copySegment(_s2);}

        if (BGSegment::isXIn(sVertical.P1().x(), s.P1().x(), s.P2().x()))
        {
            //On calcule le coefficient pour le "rayon des segments" -> Voir schéma : http://i.imgur.com/K5GSdrA.png
            double coeff1 = BGSegment(s.P1(), sVertical.P1()).getCoeff();
            double coeff2 = BGSegment(s.P1(), sVertical.P2()).getCoeff();

            int diffPoints = s.P2().x() - sVertical.P1().x();

            int posX1 = sVertical.P1().x() + diffPoints;
            if (posX1 < 0) posX1 = 0;
            int posX2 = sVertical.P2().x() + diffPoints;
            if (posX2 < 0) posX2 = 0;
            double posY1 = sVertical.P1().y() + diffPoints * coeff1;
            if (posY1 < 0) posY1 = 0;
            double posY2 = sVertical.P2().y() + diffPoints * coeff2;
            if (posY2 < 0) posY2 = 0;

            BGSegment resultSegment = BGSegment(BGPoint(posX1, (unsigned int)(posY1)), BGPoint(posX2, (unsigned int)(posY2)));

            return BGSegment::isYIn(s.P2().y(), resultSegment);
        }
        else
        {
            return false;
        }
    }
    else
    {
        double a1 = _s1.getCoeff();
        double b1 = _s1.getIntercept();

        double a2 = _s2.getCoeff();
        double b2 = _s2.getIntercept();

        //std::cout << a1 << "x + " << b1 << std::endl << a2 << "x + " << b2 << std::endl;

        if (a1 == a2) //Segments parallèles (coefficients directeurs égaux)
        {
            return false;
        }
        else
        {
            double xInter = (b2 - b1) / (a2 - a1); //L'abscisse du point d'intersection des 2 segments
            if (xInter < 0) xInter *= -1; //Ce n'est pas un plan comme en maths
            //std::cout << "Intersection : " << xInter << std::endl;
            return BGSegment::isXIn(xInter, _s1) && BGSegment::isXIn(xInter, _s2);
        }
    }
}

BGSegment BGSegment::copySegment(const BGSegment& _segment)
{
    return BGSegment(_segment.P1(), _segment.P2());
}

BGPoint BGSegment::operator[] (char _index) const
{
    switch(_index)
    {
        case 0: return m_p1;
        case 1: return m_p2;
        default:
            std::cout << "Erreur : Index non compris entre 0 et 1 inclus !" << std::endl;
            throw BGException(2, "L'indice est incorrect, il doit être égal à 0 ou 1");
            break;
    }
}

BGPoint BGSegment::getMiddle() const
{
    return BGPoint((m_p1.x() + m_p2.x()) / 2, (m_p1.y() + m_p2.y()) / 2); //Il y a forcément de l'imprécision étant donné que ce sont des nombres entiers
}

BGPoint BGSegment::getMiddle(const BGSegment& _segment)
{
    return _segment.getMiddle();
}

std::pair < double, int > BGSegment::getLineEquation() const
{
    double a = (m_p2.y() - m_p1.y()) / (m_p2.x() - m_p1.x());
    if (a < 0) a *= -1;
    int x = (int)(m_p1.y() - m_p1.x() * a);
    return std::make_pair(a, x);
}

std::pair < double, int > BGSegment::getLineEquation(const BGSegment& _segment)
{
    return _segment.getLineEquation();
}
