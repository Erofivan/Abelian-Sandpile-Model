#pragma once

#include <utility>

#include "dynamic_structures.h"

void hilbert(int n, int x, int y, 
             int xi, int xj, 
             int yi, int yj, 
             std::vector<std::pair<int, int>>& points);

std::vector<std::pair<int, int>> generate_hilbert_curve(int order);

void distribute_sand_by_iteration(std::unordered_map<std::pair<int, int>, int>& sediment);

void distribute_sand(std::unordered_map<std::pair<int, int>, int>& sediment);