#include "CCanvas.h"
#include <SFML/Graphics.hpp>

CCanvas::CCanvas(sf::RenderWindow& window) : m_window(window) {}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor) {
    sf::VertexArray line(sf::PrimitiveType::Lines, 2);
    line[0].position = sf::Vector2f(static_cast<float>(from.x), static_cast<float>(from.y));
    line[0].color = ConvertColor(lineColor);
    line[1].position = sf::Vector2f(static_cast<float>(to.x), static_cast<float>(to.y));
    line[1].color = ConvertColor(lineColor);
    m_window.draw(line);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) {
    sf::ConvexShape polygon;
    polygon.setPointCount(points.size());
    polygon.setFillColor(ConvertColor(fillColor));
    for (size_t i = 0; i < points.size(); ++i) {
        polygon.setPoint(i, sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y)));
    }
    m_window.draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor) {
    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(
        sf::Vector2f(
            static_cast<float>(center.x - radius),
            static_cast<float>(center.y - radius)
        )
    );
    circle.setOutlineColor(ConvertColor(lineColor));
    circle.setOutlineThickness(1.f);
    circle.setFillColor(sf::Color::Transparent);
    m_window.draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor) {
    sf::CircleShape circle(static_cast<float>(radius));
    circle.setPosition(
        sf::Vector2f(
            static_cast<float>(center.x - radius),
            static_cast<float>(center.y - radius)
        )
    );
    circle.setFillColor(ConvertColor(fillColor));
    m_window.draw(circle);
}

sf::Color CCanvas::ConvertColor(uint32_t color) const {
    return sf::Color(
        static_cast<uint8_t>((color >> 16) & 0xFF), // R
        static_cast<uint8_t>((color >> 8) & 0xFF),  // G
        static_cast<uint8_t>(color & 0xFF)          // B
    );
}