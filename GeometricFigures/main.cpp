#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include "IShape.h"
#include "ShapeProcessor.h"
#include <SFML/Graphics.hpp>

int main()
{
    std::vector<std::shared_ptr<IShape>> shapes;
    std::ifstream input("input.txt");
    if (!input.is_open()) 
    {
        std::cerr << "Error opening input.txt\n";
        return 1;
    }
    ShapeProcessing::ReadShapesFromStream(input, shapes);

    if (shapes.empty())
    {
        std::cout << "No valid shapes were entered.\n";
        return 0;
    }

    std::shared_ptr<IShape> maxAreaShape = ShapeProcessing::FindShapeWithLargestArea(shapes);
    std::shared_ptr<IShape> minPerimeterShape = ShapeProcessing::FindShapeWithSmallestPerimeter(shapes);

    ShapeProcessing::PrintShapeAnalysisResults(maxAreaShape, minPerimeterShape);
    
    return 0;
}