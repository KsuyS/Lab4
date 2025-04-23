#include "CTriangle.h"
#include <cmath> // For std::sqrt
#include <sstream>
#include <iomanip> // For std::fixed, std::setprecision
#include <stdexcept> // For area calculation check

CTriangle::CTriangle(CPoint v1, CPoint v2, CPoint v3, uint32_t outlineColor, uint32_t fillColor)
    : m_vertex1(v1), m_vertex2(v2), m_vertex3(v3), m_outlineColor(outlineColor), m_fillColor(fillColor)
{
    // Optional: Check for collinear points (area would be 0)
    if (GetArea() < 1e-9) // Using a small epsilon for floating point comparison
    {
        // Allow degenerate triangles as per typical geometric libraries, 
        // but one might choose to throw an error here.
        // std::cout << "Warning: Triangle vertices might be collinear, area is near zero." << std::endl;
    }
}

double CTriangle::GetPerimeter() const
{
    double side1 = m_vertex1.DistanceTo(m_vertex2);
    double side2 = m_vertex2.DistanceTo(m_vertex3);
    double side3 = m_vertex3.DistanceTo(m_vertex1);
    return side1 + side2 + side3;
}

// Using Heron's formula for area
double CTriangle::GetArea() const
{
    double a = m_vertex1.DistanceTo(m_vertex2);
    double b = m_vertex2.DistanceTo(m_vertex3);
    double c = m_vertex3.DistanceTo(m_vertex1);
    double s = (a + b + c) / 2.0; // Semi-perimeter
    double areaSquared = s * (s - a) * (s - b) * (s - c);
    if (areaSquared < 0) // Can happen due to floating point inaccuracies for near-degenerate triangles
    {
        return 0.0;
    }
    return std::sqrt(areaSquared);
}

std::string CTriangle::ToString() const
{
    std::ostringstream oss;
    oss << "Triangle: V1" << m_vertex1.ToString()
        << " V2" << m_vertex2.ToString()
        << " V3" << m_vertex3.ToString();
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