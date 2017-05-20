#ifndef BG_POINT_H
#define BG_POINT_H

class BGTriangle;

class BGPoint
{
private:

    unsigned int m_x;
    unsigned int m_y;


public:
    BGPoint();
    BGPoint(unsigned int, unsigned int);
    unsigned int x() const;
    unsigned int y() const;
    void x(unsigned int);
    void y(unsigned int);
    double getCoeff(const BGPoint&) const;
    bool isDifferent(const BGPoint&) const;

    static bool areAligned(const BGPoint&, const BGPoint&, const BGPoint&);
    static double getCoeff(const BGPoint&, const BGPoint&);
    static bool areVertical(const BGPoint&, const BGPoint&);
    static bool areDifferent(const BGPoint&, const BGPoint&);
    static int getEquationValue(const BGPoint&, const BGPoint&, const BGPoint&);
    static bool isInTriangle(const BGTriangle&, const BGPoint&);

    unsigned int operator[] (char);
};


#endif
