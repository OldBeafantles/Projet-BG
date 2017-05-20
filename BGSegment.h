#ifndef BG_SEGMENT_H
#define BG_SEGMENT_H

#include "BGPoint.h"
#include <utility>

class BGSegment
{
private:

    BGPoint m_p1;
    BGPoint m_p2;

public:

    BGSegment();
    BGSegment(const BGPoint&, const BGPoint&);
    BGSegment(unsigned int, unsigned int, unsigned int, unsigned int);
    BGPoint P1() const;
    BGPoint P2() const;
    void P1(const BGPoint&);
    void P2(const BGPoint&);
    bool isVertical() const;
    double getCoeff() const;
    double getIntercept() const;
    BGPoint getMiddle() const;
    std::pair < double, int > getLineEquation() const;

    static BGSegment copySegment(const BGSegment&);

    static bool areSecant(const BGSegment&, const BGSegment&);
    static bool isXIn(double, const BGSegment&);
    static bool isXIn(double, unsigned int, unsigned int);
    static bool isYIn(unsigned int, const BGSegment&);
    static BGPoint getMiddle(const BGSegment&);
    static std::pair < double, int > getLineEquation(const BGSegment&);

    BGPoint operator[] (char) const;
};


#endif
