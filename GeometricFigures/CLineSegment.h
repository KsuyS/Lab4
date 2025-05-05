#pragma once
#include "IShape.h"
#include "CPoint.h"
#include "ICanvas.h"
#include "ICanvasDrawable.h"

class CLineSegment : public IShape, public ICanvasDrawable
{
public:
    CLineSegment(CPoint start, CPoint end, uint32_t outlineColor);

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetOutlineColor() const override;

    CPoint GetStartPoint() const;
    CPoint GetEndPoint() const;
    void Draw(ICanvas& canvas) const;

private:
    CPoint m_startPoint;
    CPoint m_endPoint;
    uint32_t m_outlineColor;
};