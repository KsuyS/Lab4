#include "Utils.h"
#include "ISolidShape.h" // For dynamic_cast
#include <iostream>
#include <sstream>
#include <iomanip> // For std::hex, std::setfill, std::setw, std::fixed, std::setprecision
#include <stdexcept> // For std::invalid_argument

namespace Utils
{
    uint32_t ParseColor(const std::string& hexStr)
    {
        if (hexStr.length() != 6)
        {
            throw std::invalid_argument("Invalid hex color string length: " + hexStr);
        }
        try
        {
            return static_cast<uint32_t>(std::stoul(hexStr, nullptr, 16));
        }
        catch (const std::invalid_argument& e)
        {
            throw std::invalid_argument("Invalid hex color string format: " + hexStr);
        }
        catch (const std::out_of_range& e)
        {
            throw std::out_of_range("Hex color string value out of range: " + hexStr);
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
        std::cout << "Shape Type Specifics: " << shape.ToString() << std::endl;
        std::cout << "Area: " << shape.GetArea() << std::endl;
        std::cout << "Perimeter: " << shape.GetPerimeter() << std::endl;
        std::cout << "Outline Color: " << ColorToString(shape.GetOutlineColor()) << std::endl;

        // Check if it's a solid shape to print fill color
        const ISolidShape* solidShape = dynamic_cast<const ISolidShape*>(&shape);
        if (solidShape)
        {
            std::cout << "Fill Color: " << ColorToString(solidShape->GetFillColor()) << std::endl;
        }
        std::cout << "-----------------------------" << std::endl;
    }
}