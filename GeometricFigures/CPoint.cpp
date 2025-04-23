#include "CPoint.h"
#include <iomanip>

CPoint::CPoint(double x, double y) : x(x), y(y) {}

std::string CPoint::ToString() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << "(" << x << ", " << y << ")";
    return oss.str();
}

double CPoint::DistanceTo(const CPoint& other) const
{
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}