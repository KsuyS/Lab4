#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include "IShape.h"
#include "ShapeProcessor.h"
#include <SFML/Graphics.hpp>
#include "ICanvasDrawable.h"
#include "CCanvas.h"

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
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Shapes Visualization");
    CCanvas canvas(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        for (const auto& shape : shapes)
        {
            auto drawableShape = std::dynamic_pointer_cast<ICanvasDrawable>(shape);
            if (drawableShape)
            {
                drawableShape->Draw(canvas);
            }
        }

        window.display();
    }

    return 0;
}