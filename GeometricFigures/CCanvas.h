#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "CPoint.h"
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
    explicit CCanvas(sf::RenderWindow& window);

    void DrawLine(CPoint from, CPoint to, uint32_t lineColor);
    void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor);
    void DrawCircle(CPoint center, double radius, uint32_t lineColor);
    void FillCircle(CPoint center, double radius, uint32_t fillColor);

private:
    sf::RenderWindow& m_window;
    sf::Color ConvertColor(uint32_t color) const;
};