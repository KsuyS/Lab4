#pragma once

#include <vector>
#include <string>
#include <memory>   // For std::shared_ptr
#include <iostream> // For std::istream

// Forward-declare IShape to avoid including its full header here if not strictly necessary
// (���� ��� std::shared_ptr<IShape> ������ ����������� IShape ��� ����� ����������� �����������)
// � ������ ������, ��� ��� ������� ���������/���������� std::shared_ptr<IShape>,
// � ��� ���� �������� ������ �� ���������, ��� ����� �������� IShape.h.
#include "IShape.h" // Required for std::shared_ptr<IShape> in function signatures

namespace ShapeProcessing
{
    // ������� ��� �������� ������ � �������� ������
    std::shared_ptr<IShape> ParseShape(const std::string& line);

    // ������� ��� ���������� ����� �� ������ �����
    void ReadShapesFromStream(std::istream& input, std::vector<std::shared_ptr<IShape>>& shapes);

    // ������� ��� ������ ������ � ���������� ��������
    std::shared_ptr<IShape> FindShapeWithLargestArea(const std::vector<std::shared_ptr<IShape>>& shapes);

    // ������� ��� ������ ������ � ���������� ����������
    std::shared_ptr<IShape> FindShapeWithSmallestPerimeter(const std::vector<std::shared_ptr<IShape>>& shapes);

    // ������� ��� ������ �����������
    void PrintShapeAnalysisResults(
        const std::shared_ptr<IShape>& maxAreaShape,
        const std::shared_ptr<IShape>& minPerimeterShape);

} // namespace ShapeProcessing