#ifndef BG_POLYGON_H
#define BG_POLYGON_H

#include "BGPoint.h"
#include "BGTriangle.h"
#include <vector>

class BGPolygon
{
private:

    std::vector < BGPoint > m_points;
    bool m_finished;
    static const unsigned char m_nbMaxPoints;

public:

    BGPolygon();
    BGPoint operator[] (char) const;
    BGPoint getPoint(unsigned char) const;
    bool isFinished() const;

    bool addPoint(const BGPoint&); //Renvoie vrai si l'ajout du point a été réalisé, renvoie faux sinon
    bool delPoint(char = -1); //Par défaut, cela supprimera le dernier point, sinon, utilise l'indice donné en paramètre (si c'est possible)
    bool insertPoint(const BGPoint&, char = -1); //L'insère à la fin par défaut
    bool movePoint(const BGPoint&, char = -1); //Change la position d'un point avec un autre selon son indice, si cela est possible
    bool autoFinish();
    unsigned char size() const;

    std::vector < BGTriangle > triangulate() const;
    static std::vector < BGTriangle > triangulateAPolygon(BGPolygon*);
    unsigned char getLeftVertice() const;
    unsigned char getNeighbourVertice(unsigned char, char) const;

    static unsigned char getNeighbourVertice(unsigned char, char, unsigned char);
    static unsigned char getLeftVertice(std::vector < BGPoint* >);
};

#endif
