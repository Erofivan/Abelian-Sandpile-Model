#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <limits>
#include <tuple>
#include <cstdint>

#include "parser.h"
#include "dynamic_structures.h"

struct pixel {
    uint8_t value;
};

string itos(long long value);

void FillPalette(uint8_t palette[], ArgValues arg_values, int size = 20);

void FillWithValues(string& str, string& dirname, 
                pixel** pixels, int width, int height, ArgValues arg_values);

void ConverToBmp(unordered_map<std::pair<int, int>, int>& sediment,
                 string& dirname, ArgValues arg_values, int name = 0);

void ConverToBmp(vector<std::tuple<int, int, int>>& data,
                 string& dirname, ArgValues arg_values, int name = 0);