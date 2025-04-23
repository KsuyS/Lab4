#pragma once
#include <string>
#include <sstream>
#include <cmath>

class CPoint
{
public:
    double x, y;

    CPoint(double x = 0.0, double y = 0.0);
    std::string ToString() const;
    double DistanceTo(const CPoint& other) const;
};