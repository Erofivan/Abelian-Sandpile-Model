#pragma once

#include "dynamic_structures.h"

struct ArgValues {
    string input_path;
    string output_path;
    int max_iter = 0;
    int freq = 0;
    size_t max_option_size = 0;
    string palette;
    bool stats = false;
    bool help = false;
};

int StringToInt(string str);

bool DetectNumber(string s);

void FillArgValues(ArgValues& arg_value, string key, string value);

bool ProcessCommand(const string arg, ArgValues& arg_values,
                    unordered_map<string, string>& valid_commands_list);

ArgValues Parser(const int argc, char* argv[], 
                 unordered_map<string, string>& valid_commands_list);

void FillValidCommandList(unordered_map<string, string>& valid_commands_list);