#include "CTriangle.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <stdexcept>

CTriangle::CTriangle(CPoint v1, CPoint v2, CPoint v3, uint32_t outlineColor, uint32_t fillColor)
    : m_vertex1(v1), m_vertex2(v2), m_vertex3(v3), m_outlineColor(outlineColor), m_fillColor(fillColor) {}

double CTriangle::GetPerimeter() const
{
    double side1 = m_vertex1.DistanceTo(m_vertex2);
    double side2 = m_vertex2.DistanceTo(m_vertex3);
    double side3 = m_vertex3.DistanceTo(m_vertex1);
    return side1 + side2 + side3;
}

double CTriangle::GetArea() const
{
    double a = m_vertex1.DistanceTo(m_vertex2);
    double b = m_vertex2.DistanceTo(m_vertex3);
    double c = m_vertex3.DistanceTo(m_vertex1);
    double s = (a + b + c) / 2.0;
    double areaSquared = s * (s - a) * (s - b) * (s - c);
    return std::sqrt(areaSquared);
}

std::string CTriangle::ToString() const
{
    std::ostringstream oss;
    oss << "Triangle: V1" << m_vertex1.ToString() << " V2" << m_vertex2.ToString() << " V3" << m_vertex3.ToString();
    return oss.str();
}

uint32_t CTriangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
    return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
    return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
    return m_vertex3;
}

void CTriangle::Draw(ICanvas& canvas) const
{
    std::vector<CPoint> vertices{ m_vertex1, m_vertex2, m_vertex3 };
    canvas.FillPolygon(vertices, m_fillColor);
    canvas.DrawLine(m_vertex1, m_vertex2, m_outlineColor);
    canvas.DrawLine(m_vertex2, m_vertex3, m_outlineColor);
    canvas.DrawLine(m_vertex3, m_vertex1, m_outlineColor);
}