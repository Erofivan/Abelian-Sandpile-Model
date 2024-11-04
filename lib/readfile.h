#ifndef FILEREADER_H
#define FILEREADER_H

#include <tuple>
#include <fstream>
#include <sstream>
#include <cstring>

#include "dynamic_structures.h"

vector<std::tuple<int, int, int>> ReadCoordinates(string& str);

#endif
