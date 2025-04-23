#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory> // For std::shared_ptr, std::make_shared
#include <limits> // For std::numeric_limits
#include <stdexcept> // For std::exception

#include "CPoint.h"
#include "IShape.h"
#include "ISolidShape.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCircle.h"
#include "Utils.h" // For ParseColor and PrintShapeDetails

// Function to parse a line and create a shape
std::shared_ptr<IShape> ParseShape(const std::string& line)
{
    std::istringstream iss(line);
    std::string shapeType;
    iss >> shapeType;

    try
    {
        if (shapeType == "line")
        {
            double x1, y1, x2, y2;
            std::string outlineColorStr;
            if (!(iss >> x1 >> y1 >> x2 >> y2 >> outlineColorStr))
                throw std::runtime_error("Invalid line parameters.");
            return std::make_shared<CLineSegment>(
                CPoint(x1, y1), CPoint(x2, y2), Utils::ParseColor(outlineColorStr)
            );
        }
        else if (shapeType == "rectangle")
        {
            double x, y, width, height;
            std::string outlineColorStr, fillColorStr;
            if (!(iss >> x >> y >> width >> height >> outlineColorStr >> fillColorStr))
                throw std::runtime_error("Invalid rectangle parameters.");
            return std::make_shared<CRectangle>(
                CPoint(x, y), width, height,
                Utils::ParseColor(outlineColorStr), Utils::ParseColor(fillColorStr)
            );
        }
        else if (shapeType == "triangle")
        {
            double x1, y1, x2, y2, x3, y3;
            std::string outlineColorStr, fillColorStr;
            if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineColorStr >> fillColorStr))
                throw std::runtime_error("Invalid triangle parameters.");
            return std::make_shared<CTriangle>(
                CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3),
                Utils::ParseColor(outlineColorStr), Utils::ParseColor(fillColorStr)
            );
        }
        else if (shapeType == "circle")
        {
            double cx, cy, radius;
            std::string outlineColorStr, fillColorStr;
            if (!(iss >> cx >> cy >> radius >> outlineColorStr >> fillColorStr))
                throw std::runtime_error("Invalid circle parameters.");
            return std::make_shared<CCircle>(
                CPoint(cx, cy), radius,
                Utils::ParseColor(outlineColorStr), Utils::ParseColor(fillColorStr)
            );
        }
        else
        {
            std::cerr << "Unknown shape type: " << shapeType << std::endl;
            return nullptr;
        }
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Error parsing shape '" << shapeType << "': " << e.what() << std::endl;
        return nullptr;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error parsing shape '" << shapeType << "': " << e.what() << std::endl;
        return nullptr;
    }
    catch (const std::exception& e) // Catch any other standard exceptions
    {
        std::cerr << "An unexpected error occurred while parsing shape '" << shapeType << "': " << e.what() << std::endl;
        return nullptr;
    }
}


int main()
{
    std::vector<std::shared_ptr<IShape>> shapes;
    std::string line;

    std::cout << "Enter shape commands (e.g., 'rectangle 10 20 5 8 ff0000 00ff00'), one per line. Press Ctrl+D (Linux/macOS) or Ctrl+Z then Enter (Windows) to finish." << std::endl;

    while (std::getline(std::cin, line))
    {
        if (line.empty()) continue; // Skip empty lines

        std::shared_ptr<IShape> shape = ParseShape(line);
        if (shape)
        {
            shapes.push_back(shape);
        }
    }

    if (shapes.empty())
    {
        std::cout << "No shapes were entered." << std::endl;
        return 0;
    }

    // Find shape with largest area
    std::shared_ptr<IShape> maxAreaShape = shapes[0];
    for (const auto& shape : shapes)
    {
        if (shape->GetArea() > maxAreaShape->GetArea())
        {
            maxAreaShape = shape;
        }
    }

    // Find shape with smallest perimeter
    std::shared_ptr<IShape> minPerimeterShape = shapes[0];
    for (const auto& shape : shapes)
    {
        if (shape->GetPerimeter() < minPerimeterShape->GetPerimeter())
        {
            minPerimeterShape = shape;
        }
    }

    std::cout << "\n--- Shape with Largest Area ---" << std::endl;
    Utils::PrintShapeDetails(*maxAreaShape);

    std::cout << "\n--- Shape with Smallest Perimeter ---" << std::endl;
    Utils::PrintShapeDetails(*minPerimeterShape);

    return 0;
}