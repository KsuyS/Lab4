#include <iostream>
#include <vector>
#include <memory>
#include "IShape.h"
#include "ShapeProcessor.h"

int main()
{
    std::vector<std::shared_ptr<IShape>> shapes;
    ShapeProcessing::ReadShapesFromStream(std::cin, shapes);

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