#include "CRectangle.h"
#include <sstream>
#include <iomanip>
#include <iostream>

CRectangle::CRectangle(CPoint topLeft, double width, double height, uint32_t outlineColor, uint32_t fillColor)
    : m_topLeft(topLeft), m_width(width), m_height(height), m_outlineColor(outlineColor), m_fillColor(fillColor)
{
    if (width < 0 || height < 0)
    {
        std::cout << "Rectangle width and height must be non-negative.";
    }
}

double CRectangle::GetArea() const
{
    return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
    return 2 * (m_width + m_height);
}

std::string CRectangle::ToString() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "Rectangle: TopLeft" << m_topLeft.ToString() << " Width(" << m_width << ") Height(" << m_height << ")";
    return oss.str();
}

uint32_t CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
    return m_topLeft;
}

CPoint CRectangle::GetRightBottom() const
{
    return CPoint(m_topLeft.x + m_width, m_topLeft.y + m_height);
}

double CRectangle::GetWidth() const
{
    return m_width;
}

double CRectangle::GetHeight() const
{
    return m_height;
}

void CRectangle::Draw(ICanvas& canvas) const
{
    std::vector<CPoint> vertices
    {
        m_topLeft,
        CPoint(m_topLeft.x + m_width, m_topLeft.y),
        CPoint(m_topLeft.x + m_width, m_topLeft.y + m_height),
        CPoint(m_topLeft.x, m_topLeft.y + m_height)
    };
    canvas.FillPolygon(vertices, m_fillColor);
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        canvas.DrawLine(vertices[i], vertices[(i + 1) % vertices.size()], m_outlineColor);
    }
}