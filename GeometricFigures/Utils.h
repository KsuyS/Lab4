#pragma once
#include <string>
#include <cstdint>
#include <memory>
#include "IShape.h"

namespace Utils
{
    uint32_t ParseColor(const std::string& hexStr);
    std::string ColorToString(uint32_t color);
    void PrintShapeDetails(const IShape& shape);
}