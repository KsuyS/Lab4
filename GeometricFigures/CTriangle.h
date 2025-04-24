#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
#include "ICanvasDrawable.h"

class CTriangle : public ISolidShape, public ICanvasDrawable
{
public:
    CTriangle(CPoint v1, CPoint v2, CPoint v3, uint32_t outlineColor, uint32_t fillColor);

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetOutlineColor() const override;
    uint32_t GetFillColor() const override;
    void Draw(ICanvas& canvas) const override;

    CPoint GetVertex1() const;
    CPoint GetVertex2() const;
    CPoint GetVertex3() const;

private:
    CPoint m_vertex1, m_vertex2, m_vertex3;
    uint32_t m_outlineColor;
    uint32_t m_fillColor;
};