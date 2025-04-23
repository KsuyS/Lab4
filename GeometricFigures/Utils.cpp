#include "Utils.h"
#include "ISolidShape.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

namespace Utils
{
    uint32_t ParseColor(const std::string& hexStr)
    {
        if (hexStr.length() != 6)
        {
            std::cout << "Invalid hex color string length";
        }
        try
        {
            return static_cast<uint32_t>(std::stoul(hexStr, nullptr, 16));
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "Invalid hex color string format";
        }
    }

    std::string ColorToString(uint32_t color)
    {
        std::ostringstream oss;
        oss << "#" << std::hex << std::setfill('0') << std::setw(6) << color;
        return oss.str();
    }

    void PrintShapeDetails(const IShape& shape)
    {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Shape Type Specifics: " << shape.ToString() << "\n";
        std::cout << "Area: " << shape.GetArea() << "\n";
        std::cout << "Perimeter: " << shape.GetPerimeter() << "\n";
        std::cout << "Outline Color: " << ColorToString(shape.GetOutlineColor()) << "\n";

        const ISolidShape* solidShape = dynamic_cast<const ISolidShape*>(&shape);
        if (solidShape)
        {
            std::cout << "Fill Color: " << ColorToString(solidShape->GetFillColor()) << "\n";
        }
        std::cout << "\n";;
    }
}