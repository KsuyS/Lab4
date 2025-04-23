#include <iostream>
#include <vector>
#include <memory> // For std::shared_ptr

#include "IShape.h" // Только для std::vector<std::shared_ptr<IShape>>
#include "ShapeProcessor.h" // Для всех наших вспомогательных функций

int main()
{
    std::vector<std::shared_ptr<IShape>> shapes;

    // Используем функции из нашего нового модуля
    ShapeProcessing::ReadShapesFromStream(std::cin, shapes);

    if (shapes.empty())
    {
        std::cout << "No valid shapes were entered." << std::endl;
        return 0;
    }

    std::shared_ptr<IShape> maxAreaShape = ShapeProcessing::FindShapeWithLargestArea(shapes);
    std::shared_ptr<IShape> minPerimeterShape = ShapeProcessing::FindShapeWithSmallestPerimeter(shapes);

    ShapeProcessing::PrintShapeAnalysisResults(maxAreaShape, minPerimeterShape);

    return 0;
}