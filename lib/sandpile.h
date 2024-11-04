#pragma once

#include <cmath>
#include <limits>
#include <utility>

#include "dynamic_structures.h"

void distribute_sand_by_iteration(unordered_map<std::pair<int, int>, int>& sediment);

void calculate_bounds(vector<std::tuple<int, int, int>>& sediment,
                      int& left_edge, int& right_edge, int& top_edge, int& bottom_edge);

void distribute_sand(vector<std::tuple<int, int, int>>& sediment);