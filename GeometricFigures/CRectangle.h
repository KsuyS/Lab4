#pragma once
#include "ISolidShape.h"
#include "ICanvasDrawable.h"
#include "CPoint.h"

class CRectangle : public ISolidShape, public ICanvasDrawable
{
public:
    CRectangle(CPoint topLeft, double width, double height, uint32_t outlineColor, uint32_t fillColor);

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetOutlineColor() const override;
    uint32_t GetFillColor() const override;
    void Draw(ICanvas& canvas) const override;

    CPoint GetLeftTop() const;
    CPoint GetRightBottom() const;
    double GetWidth() const;
    double GetHeight() const;

private:
    CPoint m_topLeft;
    double m_width;
    double m_height;
    uint32_t m_outlineColor;
    uint32_t m_fillColor;
};