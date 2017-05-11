#ifndef BG_TRIANGLE_H
#define BG_TRIANGLE_H
#include "BGPoint.h"


class BGTriangle
{

private:
    BGPoint m_p1;
    BGPoint m_p2;
    BGPoint m_p3;

public:
    BGTriangle();
    BGTriangle(BGPoint, BGPoint, BGPoint);

    BGPoint P1() const;
    BGPoint P2() const;
    BGPoint P3() const;

    BGPoint operator[] (char) const;
};

#endif
