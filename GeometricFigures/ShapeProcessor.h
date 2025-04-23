#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "IShape.h"

namespace ShapeProcessing
{
    std::shared_ptr<IShape> ParseShape(const std::string& line);

    void ReadShapesFromStream(std::istream& input, std::vector<std::shared_ptr<IShape>>& shapes);

    std::shared_ptr<IShape> FindShapeWithLargestArea(const std::vector<std::shared_ptr<IShape>>& shapes);

    std::shared_ptr<IShape> FindShapeWithSmallestPerimeter(const std::vector<std::shared_ptr<IShape>>& shapes);

    void PrintShapeAnalysisResults(const std::shared_ptr<IShape>& maxAreaShape, 
        const std::shared_ptr<IShape>& minPerimeterShape);
}