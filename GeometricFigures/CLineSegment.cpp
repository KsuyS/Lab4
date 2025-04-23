#include "CLineSegment.h"
#include <cmath>
#include <sstream>
#include <iomanip>

CLineSegment::CLineSegment(CPoint start, CPoint end, uint32_t outlineColor)
    : m_startPoint(start), m_endPoint(end), m_outlineColor(outlineColor) {}

double CLineSegment::GetArea() const
{
    return 0.0;
}

double CLineSegment::GetPerimeter() const
{
    return m_startPoint.DistanceTo(m_endPoint);
}

std::string CLineSegment::ToString() const
{
    std::ostringstream oss;
    oss << "Line Segment: Start" << m_startPoint.ToString() << " End" << m_endPoint.ToString();
    return oss.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}