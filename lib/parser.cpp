#include "parser.h"

int StringToInt(string str) {
    long long num = 0;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return -1;
        } else {
            int t = (int)(str[i]) - 48;
            num += t;
            num *= 10;
        }
        ++i;
    }
    num /= 10;
    return num;
}

bool DetectNumber(string s) {
    for (size_t i = 0; i < s.size(); ++i) {
        if (!('0' <= s[i] && s[i] <= '9')) return true;
    }
    return false;
}

void FillValidCommandList(unordered_map<string, string>& valid_commands_list) {
    valid_commands_list["-i"] = "--input";
    valid_commands_list["--input"] = nullptr;
    valid_commands_list["-o"] = "--output";
    valid_commands_list["--output"] = nullptr;
    valid_commands_list["-m"] = "--max-iter";
    valid_commands_list["--max-iter"] = nullptr;
    valid_commands_list["-f"] = "--freq";
    valid_commands_list["--freq"] = nullptr;
    valid_commands_list["-c"] = "--color";
    valid_commands_list["--color"] = nullptr;
    valid_commands_list["-s"] = "--stats";
    valid_commands_list["--stats"] = "*6#,lopj2,n1_9y";
    valid_commands_list["-h"] = "--stats";
    valid_commands_list["--help"] = "*6#,lopj2,n1_9y";
}

void FillArgValues(ArgValues& arg_value, string key, string value) {
    if (key == "-o") {
        arg_value.output_path = value;
    } else if (key == "-i") {
        arg_value.input_path = value;
    } else if (key == "-m") {
        if (DetectNumber(value)) {
            std::cerr << "error: " << key << " expects a number" << std::endl;
            return;
        }
        arg_value.max_iter = StringToInt(value);
    } else if (key == "-f") {
        if (DetectNumber(value)) {
            std::cerr << "error: " << key << " expects a number" << std::endl;
            return;
        }
        arg_value.freq = StringToInt(value);
    } else if (key == "-c") {
        arg_value.palette = value;
    } else if (key == "-s") {
        arg_value.stats = true;
    } else if (key == "-h") {
        arg_value.help = true;
    } 
}

bool ProcessCommand(const string arg, ArgValues& arg_values,
                    unordered_map<string, string>& valid_commands_list) {
    string cmd = arg.substr(0, arg.find('='));

    // Handling error arguments
    if (cmd.substr(0, 2) == "--" && cmd.size() == 2) {
        std::cerr << "error: unknown option " << arg << std::endl;
        return false; // Return if we found wrong option
    }

    if (cmd.substr(0, 1) == "-" && cmd.size() == 1) {
        std::cerr << "error: unknown option " << arg << std::endl;
        return false; // Return if we found wrong option
    }

    if (cmd.size() > arg_values.max_option_size ||
        valid_commands_list.count(cmd) == 0) {
        std::cerr << "error: unknown option " << arg << std::endl;
        return false; // Return if we found wrong option
    } else if (!(arg.substr(0,2) == "--") &&
        arg.find('=') != arg.size()) {
        std::cerr << "error: unknown option " << arg << std::endl;
        return false; // Return if we found wrong option
    }

    // Handling dublicated agruments
    if (!(valid_commands_list[cmd] == nullptr) &&
        arg.substr(0, 2) == "--") {
        std::cerr << "error: repetition of an argument " 
                  << cmd << std::endl;
        return false; // Return if we found dublicated option
    }
    //Handling arguents that do not need value
    if (valid_commands_list[arg] == "*6#,lopj2,n1_9y" ||
        valid_commands_list[valid_commands_list[arg]] == "*6#,lopj2,n1_9y") {
        FillArgValues(arg_values, arg.substr(0, 2), "");
        return false;
    }


    // Make flags for arguments that we already handled
    // Set flag that we already handled this type of argument
    string cmd_value = arg.substr(arg.find('=')+1, arg.size());
    if (arg.substr(0, 2) == "--") {
        // Handling no value providition
        if (cmd_value == "" && (cmd.find('=') != cmd.size())) {
            std::cerr << "error: " << cmd << " expects a value" << std::endl;
            return false;
        } else if (cmd_value == "" && (cmd.find('=') == cmd.size())) {
            return true;
        }
        string ShortArg = arg.substr(1, 3);
        valid_commands_list[cmd] = cmd_value;

        FillArgValues(arg_values, ShortArg, cmd_value);

        return false;
    } else {
        if (!(valid_commands_list[valid_commands_list[cmd]] == nullptr)) {
            std::cerr << "error: repetition of an argument " 
                    << cmd << std::endl;
            return false; // Return if we found dublicated option
        }
        string LongArg = valid_commands_list[cmd];
        string empty = "nl2#@. 0E2,n1_9y s*6#,lopjG ]K9j";
        valid_commands_list[LongArg] = empty; 
        return true;
    }
}


ArgValues Parser(const int argc, char* argv[], 
                 unordered_map<string, string>& valid_commands_list) {
    // Structure for containing argument values
    ArgValues arg_values;

    // We need to know max option size, so we can handle long wrong options
    for (auto& i : valid_commands_list) {
        string current_option = i.first.substr(0, i.first.find('=')); // We get the argument up to '=' sign. If '=' is not present we get whole argument. @example "--output=abc" will return "--output" and "--outputabc" will return "--outputabc"
        size_t current_option_size = current_option.size();
        if (current_option_size > arg_values.max_option_size) {
            arg_values.max_option_size = current_option_size;
        }
    }

    // Processing all arguments
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            bool is_next_arg_a_value = ProcessCommand(
                                            argv[i], 
                                            arg_values, 
                                            valid_commands_list);
            bool is_long = false;
            string argvi = argv[i];
            if (argvi.substr(0, 2) == "--") {
                is_long = true;
            }
            if (is_next_arg_a_value && is_long && i+1 != argc) {
                string argviiplus1 = argv[i+1];
                valid_commands_list[argvi] = argviiplus1;
                FillArgValues(arg_values, argvi.substr(1, 3), argv[i+1]);
                ++i;
                continue;
            } else if (is_next_arg_a_value && !(is_long) && i+1 != argc) {
                FillArgValues(arg_values, argv[i], argv[i+1]);
                ++i;
                continue;       
            } else if (is_next_arg_a_value && i+1 == argc) {
                std::cerr << "error: " << argv[i] << " expects a value" << std::endl;
            }
        } else {
            std::cerr << "error: unknown option " << argv[i] << std::endl;
        }
    }
    return arg_values;
}