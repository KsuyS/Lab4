#pragma once

#include <vector>
#include <string>
#include <memory>   // For std::shared_ptr
#include <iostream> // For std::istream

// Forward-declare IShape to avoid including its full header here if not strictly necessary
// (хотя для std::shared_ptr<IShape> полное определение IShape все равно понадобится компилятору)
// В данном случае, так как функции принимают/возвращают std::shared_ptr<IShape>,
// и эти типы являются частью их сигнатуры, нам нужно включить IShape.h.
#include "IShape.h" // Required for std::shared_ptr<IShape> in function signatures

namespace ShapeProcessing
{
    // Функция для парсинга строки и создания фигуры
    std::shared_ptr<IShape> ParseShape(const std::string& line);

    // Функция для считывания фигур из потока ввода
    void ReadShapesFromStream(std::istream& input, std::vector<std::shared_ptr<IShape>>& shapes);

    // Функция для поиска фигуры с наибольшей площадью
    std::shared_ptr<IShape> FindShapeWithLargestArea(const std::vector<std::shared_ptr<IShape>>& shapes);

    // Функция для поиска фигуры с наименьшим периметром
    std::shared_ptr<IShape> FindShapeWithSmallestPerimeter(const std::vector<std::shared_ptr<IShape>>& shapes);

    // Функция для вывода результатов
    void PrintShapeAnalysisResults(
        const std::shared_ptr<IShape>& maxAreaShape,
        const std::shared_ptr<IShape>& minPerimeterShape);

} // namespace ShapeProcessing