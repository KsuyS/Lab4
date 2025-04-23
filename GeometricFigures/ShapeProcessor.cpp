#include "ShapeProcessor.h"

#include <sstream>
#include <stdexcept>
#include <algorithm> // For std::max_element, std::min_element (if you use them)

// Include necessary shape and utility headers
#include "CPoint.h"
// IShape.h уже включен через ShapeProcessor.h
#include "ISolidShape.h" // Potentially needed if ParseShape did more type checking internally
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCircle.h"
#include "Utils.h" // For ParseColor and PrintShapeDetails

namespace ShapeProcessing
{
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
                    throw std::runtime_error("Invalid line parameters. Expected: line x1 y1 x2 y2 outline_color");
                return std::make_shared<CLineSegment>(
                    CPoint(x1, y1), CPoint(x2, y2), Utils::ParseColor(outlineColorStr));
            }
            else if (shapeType == "rectangle")
            {
                double x, y, width, height;
                std::string outlineColorStr, fillColorStr;
                if (!(iss >> x >> y >> width >> height >> outlineColorStr >> fillColorStr))
                    throw std::runtime_error("Invalid rectangle parameters. Expected: rectangle x y width height outline_color fill_color");
                return std::make_shared<CRectangle>(
                    CPoint(x, y), width, height,
                    Utils::ParseColor(outlineColorStr), Utils::ParseColor(fillColorStr));
            }
            else if (shapeType == "triangle")
            {
                double x1, y1, x2, y2, x3, y3;
                std::string outlineColorStr, fillColorStr;
                if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineColorStr >> fillColorStr))
                    throw std::runtime_error("Invalid triangle parameters. Expected: triangle x1 y1 x2 y2 x3 y3 outline_color fill_color");
                return std::make_shared<CTriangle>(
                    CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3),
                    Utils::ParseColor(outlineColorStr), Utils::ParseColor(fillColorStr));
            }
            else if (shapeType == "circle")
            {
                double cx, cy, radius;
                std::string outlineColorStr, fillColorStr;
                if (!(iss >> cx >> cy >> radius >> outlineColorStr >> fillColorStr))
                    throw std::runtime_error("Invalid circle parameters. Expected: circle cx cy radius outline_color fill_color");
                return std::make_shared<CCircle>(
                    CPoint(cx, cy), radius,
                    Utils::ParseColor(outlineColorStr), Utils::ParseColor(fillColorStr));
            }
            else
            {
                std::cerr << "Unknown shape type: " << shapeType << " on line: " << line << std::endl;
                return nullptr;
            }
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Error parsing '" << shapeType << "' on line '" << line << "': " << e.what() << std::endl;
            return nullptr;
        }
        catch (const std::runtime_error& e)
        {
            std::cerr << "Error parsing '" << shapeType << "' on line '" << line << "': " << e.what() << std::endl;
            return nullptr;
        }
        catch (const std::exception& e) // Catch any other standard exceptions
        {
            std::cerr << "An unexpected error occurred while parsing '" << shapeType << "' on line '" << line << "': " << e.what() << std::endl;
            return nullptr;
        }
    }

    void ReadShapesFromStream(std::istream& input, std::vector<std::shared_ptr<IShape>>& shapes)
    {
        std::cout << "Enter shape commands (e.g., 'rectangle 10 20 5 8 ff0000 00ff00'), one per line.\n"
            << "Press Ctrl+D (Linux/macOS) or Ctrl+Z then Enter (Windows) to finish." << std::endl;

        std::string line;
        while (std::getline(input, line))
        {
            if (line.empty() || line.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
            {
                continue;
            }
            std::shared_ptr<IShape> shape = ParseShape(line); // Calls ParseShape from this namespace
            if (shape)
            {
                shapes.push_back(shape);
            }
        }
    }

    std::shared_ptr<IShape> FindShapeWithLargestArea(const std::vector<std::shared_ptr<IShape>>& shapes)
    {
        if (shapes.empty())
        {
            return nullptr;
        }

        auto it = std::max_element(shapes.begin(), shapes.end(),
            [](const std::shared_ptr<IShape>& a, const std::shared_ptr<IShape>& b) {
                // Handle nullptr just in case, though our current logic tries to avoid adding them
                if (!a) return true; // consider nullptr smaller
                if (!b) return false;
                return a->GetArea() < b->GetArea();
            });

        return (it == shapes.end() || !(*it)) ? nullptr : *it; // ensure valid shape is returned
    }

    std::shared_ptr<IShape> FindShapeWithSmallestPerimeter(const std::vector<std::shared_ptr<IShape>>& shapes)
    {
        if (shapes.empty())
        {
            return nullptr;
        }

        auto it = std::min_element(shapes.begin(), shapes.end(),
            [](const std::shared_ptr<IShape>& a, const std::shared_ptr<IShape>& b) {
                if (!a) return false; // consider nullptr larger
                if (!b) return true;
                return a->GetPerimeter() < b->GetPerimeter();
            });

        return (it == shapes.end() || !(*it)) ? nullptr : *it; // ensure valid shape is returned
    }

    void PrintShapeAnalysisResults(
        const std::shared_ptr<IShape>& maxAreaShape,
        const std::shared_ptr<IShape>& minPerimeterShape)
    {
        if (maxAreaShape)
        {
            std::cout << "\n--- Shape with Largest Area ---" << std::endl;
            Utils::PrintShapeDetails(*maxAreaShape);
        }
        else
        {
            std::cout << "\nCould not determine shape with largest area (no valid shapes found or error)." << std::endl;
        }

        if (minPerimeterShape)
        {
            std::cout << "\n--- Shape with Smallest Perimeter ---" << std::endl;
            Utils::PrintShapeDetails(*minPerimeterShape);
        }
        else
        {
            std::cout << "\nCould not determine shape with smallest perimeter (no valid shapes found or error)." << std::endl;
        }
    }

} // namespace ShapeProcessing