#include "BGTriangle.h"
#include "BGException.h"
#include <iostream>

BGTriangle::BGTriangle() : m_p1(BGPoint()), m_p2(BGPoint()), m_p3(BGPoint())
{}

BGTriangle::BGTriangle(BGPoint _p1, BGPoint _p2, BGPoint _p3)
{
    m_p1 = _p1;
    m_p2 = _p2;
    m_p3 = _p3;
}

BGPoint BGTriangle::P1() const
{
    return m_p1;
}

BGPoint BGTriangle::P2() const
{
    return m_p2;
}

BGPoint BGTriangle::P3() const
{
    return m_p3;
}

BGPoint BGTriangle::operator[] (char _index) const
{
    switch (_index)
    {
        case 0: return m_p1;
        case 1: return m_p2;
        case 2: return m_p3;
        default:
            std::cout << "Erreur : Index non compris entre 0 et 1 inclus !" << std::endl;
            throw BGException(3, "L'indice est incorrect, il doit être égal à 0, 1, ou 2");
            break;
    }
}
