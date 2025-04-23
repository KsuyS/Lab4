#pragma once
#include <string>
#include <cstdint>
#include <memory> // For std::shared_ptr
#include "IShape.h" // For PrintShapeDetails

namespace Utils
{
    uint32_t ParseColor(const std::string& hexStr);
    std::string ColorToString(uint32_t color);
    void PrintShapeDetails(const IShape& shape);
}