#ifndef FILEREADER_H
#define FILEREADER_H

#include <tuple>
#include <fstream>
#include <sstream>
#include <cstring>

#include "dynamic_structures.h"

using string;
using vector;

string itos(long long value);
vector<std::tuple<int, int, int>> ReadCoordinates(string& str);

#endif
