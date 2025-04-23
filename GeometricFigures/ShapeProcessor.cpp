#include "ShapeProcessor.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "CPoint.h"
#include "ISolidShape.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCircle.h"
#include "Utils.h"

namespace ShapeProcessing
{
    std::shared_ptr<IShape> ParseLine(const std::istringstream& inputStream)
    {
        std::istringstream iss(inputStream.str());
        std::string shapeType;
        iss >> shapeType;
        double x1, y1, x2, y2;
        std::string outlineColorStr;
        if (!(iss >> x1 >> y1 >> x2 >> y2 >> outlineColorStr))
        {
            std::cout << "Invalid line parameters.Expected: line x1 y1 x2 y2 outline_color";
            return nullptr;
        }
        return std::make_shared<CLineSegment>(CPoint(x1, y1), CPoint(x2, y2), Utils::ParseColor(outlineColorStr));
    }

    std::shared_ptr<IShape> ParseRectangle(const std::istringstream& inputStream)
    {
        std::istringstream iss(inputStream.str());
        std::string shapeType;
        iss >> shapeType;
        double x, y, width, height;
        std::string outlineColorStr, fillColorStr;
        if (!(iss >> x >> y >> width >> height >> outlineColorStr >> fillColorStr))
        {
            std::cout << "Invalid rectangle parameters. Expected: rectangle x y width height outline_color fill_color";
            return nullptr;
        }
        return std::make_shared<CRectangle>(CPoint(x, y), width, height, Utils::ParseColor(outlineColorStr), 
            Utils::ParseColor(fillColorStr));
    }

    std::shared_ptr<IShape> ParseTriangle(const std::istringstream& inputStream)
    {
        std::istringstream iss(inputStream.str());
        std::string shapeType;
        iss >> shapeType;
        double x1, y1, x2, y2, x3, y3;
        std::string outlineColorStr, fillColorStr;
        if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineColorStr >> fillColorStr))
        {
            std::cout << "Invalid triangle parameters. Expected: triangle x1 y1 x2 y2 x3 y3 outline_color fill_color";
            return nullptr;
        }
        return std::make_shared<CTriangle>(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3),
            Utils::ParseColor(outlineColorStr), Utils::ParseColor(fillColorStr));
    }

    std::shared_ptr<IShape> ParseCircle(const std::istringstream& inputStream)
    {
        std::istringstream iss(inputStream.str());
        std::string shapeType; iss >> shapeType;
        double cx, cy, radius;
        std::string outlineColorStr, fillColorStr;
        if (!(iss >> cx >> cy >> radius >> outlineColorStr >> fillColorStr))
        {
            std::cout << "Invalid circle parameters. Expected: circle cx cy radius outline_color fill_color";
            return nullptr;
        }
        return std::make_shared<CCircle>(CPoint(cx, cy), radius, Utils::ParseColor(outlineColorStr), Utils::ParseColor(fillColorStr));
    }

    std::shared_ptr<IShape> ParseShape(const std::string& inputStream)
    {
        std::istringstream iss(inputStream);
        std::string shapeType;
        iss >> shapeType;
        try
        {
            if (shapeType == "line")
            {
                return ParseLine(iss);
            }
            else if (shapeType == "rectangle")
            {
                return ParseRectangle(iss);
            }
            else if (shapeType == "triangle")
            {
                return ParseTriangle(iss);
            }
            else if (shapeType == "circle")
            {
                return ParseCircle(iss);
            }
            else
            {
                std::cerr << "Unknown shape type: " << shapeType << " on input line: " << inputStream << "\n";
                return nullptr;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "An unexpected error occurred while parsing '" << shapeType << "' on input line '" << inputStream << "': " << e.what() << "\n";
            return nullptr;
        }
    }

    void ReadShapesFromStream(std::istream& input, std::vector<std::shared_ptr<IShape>>& shapes)
    {
        std::string line;
        while (std::getline(input, line))
        {
            if (line.empty() || line.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
            {
                continue;
            }
            std::shared_ptr<IShape> shape = ParseShape(line);
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

        auto shape = std::max_element(shapes.begin(), shapes.end(),
            [](const std::shared_ptr<IShape>& shape1, const std::shared_ptr<IShape>& shape2)
            {
                if (!shape1) return true;
                if (!shape2) return false;
                return shape1->GetArea() < shape2->GetArea();
            });

        return (shape == shapes.end() || !(*shape)) ? nullptr : *shape;
    }

    std::shared_ptr<IShape> FindShapeWithSmallestPerimeter(const std::vector<std::shared_ptr<IShape>>& shapes)
    {
        if (shapes.empty())
        {
            return nullptr;
        }

        auto shape = std::min_element(shapes.begin(), shapes.end(),
            [](const std::shared_ptr<IShape>& shape1, const std::shared_ptr<IShape>& shape2)
            {
                if (!shape1) return false;
                if (!shape2) return true;
                return shape1->GetPerimeter() < shape2->GetPerimeter();
            });

        return (shape == shapes.end() || !(*shape)) ? nullptr : *shape;
    }

    void PrintShapeAnalysisResults(const std::shared_ptr<IShape>& maxAreaShape, const std::shared_ptr<IShape>& minPerimeterShape)
    {
        if (maxAreaShape)
        {
            std::cout << "\nShape with Largest Area:\n" << "\n";
            Utils::PrintShapeDetails(*maxAreaShape);
        }
        else
        {
            std::cout << "\nCould not determine shape with largest area." << "\n";
        }

        if (minPerimeterShape)
        {
            std::cout << "\nShape with Smallest Perimeter:" << "\n";
            Utils::PrintShapeDetails(*minPerimeterShape);
        }
        else
        {
            std::cout << "\nCould not determine shape with smallest perimeter." << "\n";
        }
    }
}