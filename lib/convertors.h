#pragma once

#include <limits>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <tuple>
#include <cstdint>

#include "dynamic_structures.h"

struct pixel {
    uint8_t value;
};

void FillWithValues(string& str, std::string& dirname, 
                    pixel** pixels, int width, int height);

void ConverToBmp(unordered_map<std::pair<int, int>, int>& sediment,
                 string& dirname, int name = 0);