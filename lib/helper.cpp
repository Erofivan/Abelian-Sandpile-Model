#include "helper.h"



void ErrorMessage(size_t ErrorCode) {
    switch(ErrorCode) {
        case 0: {
            std::cerr << "error: input path was not provided" << std::endl;
            break;
        }
        case 1: {
            std::cerr << "error: output path was not provided" << std::endl;
            break;
        }
        case 2: {
            std::cout << "Usage: labwork3.exe [commands]" 
            << std::endl << std::endl <<
        "There are list of commands:"
            << std::endl << std::endl <<
        "Base commands:"
        << std::endl <<
            "[-i <path> | --input=<path>]        Specify path to the file with initial data"
            << std::endl <<
            "[-o <path> | --output=<path>]       Specify path to the output file"
            << std::endl <<
            "[-m <value> | --max-iter=<value>]   Set max amount of iterations"
            << std::endl <<
            "[-f <value> | --freq=<value>]       Set frequency of iteartion saves"
        << std::endl << std::endl <<
        "Additional command:"
        << std::endl <<
            "[-c <value> | --set-color=<value>]  Set sandpile color"
            << std::endl <<
            "[-h | --help]                       Get help with commands"
            << std::endl <<
            "[-s | --stats]                      Print command options"
        << std::endl << std::endl <<
        "See 'labwork3 --help <command>' to read about a specific command" << std::endl;
            break;
        }
        default: {
            std::cerr << "error: unknown error has occured" << std::endl;
            break;
        }
    }
}

void PreviewValues(ArgValues& arg_values) {
    bool HasErrorOccured = false;
    if (arg_values.input_path == nullptr) {
        ErrorMessage(ErrorCode(InputPathWasNotProvided));
        HasErrorOccured = true;
    }
    if (arg_values.output_path == nullptr) {
        ErrorMessage(ErrorCode(OutputPathWasNotProvided));
        HasErrorOccured = true;
    }
    if (arg_values.stats) {
        std::cout << std::endl;
        std::cout << "Input path: " << arg_values.input_path << std::endl;
        std::cout << "Outputh folder: " << arg_values.output_path << std::endl;
        std::cout << "Max iter: " << arg_values.max_iter << std::endl;
        std::cout << "Freq: " << arg_values.freq << std::endl;
        if (arg_values.palette == nullptr) {
            std::cout << "Colors: " << "FFFFFF,00FF00,800080,FFFF00,000000" << std::endl;
        } else {
            std::cout << "Colors: " << arg_values.palette << std::endl;
        }
    }
    if (arg_values.help) {
        std::cout << std::endl;
        std::cout << "Usage: labwork3.exe [commands]" 
            << std::endl << std::endl <<
        "There are list of commands:"
            << std::endl << std::endl <<
        "Base commands:"
        << std::endl <<
            "[-i <path> | --input=<path>]        Specify path to the file with initial data"
            << std::endl <<
            "[-o <path> | --output=<path>]       Specify path to the output file"
            << std::endl <<
            "[-m <value> | --max-iter=<value>]   Set max amount of iterations"
            << std::endl <<
            "[-f <value> | --freq=<value>]       Set frequency of iteartion saves"
        << std::endl << std::endl <<
        "Additional command:"
        << std::endl <<
            "[-c <value> | --set-color=<value>]  Set sandpile color"
            << std::endl <<
            "[-h | --help]                       Get help with commands"
            << std::endl <<
            "[-s | --stats]                      Print command options"
        << std::endl << std::endl <<
        "See 'labwork3 --help <command>' to read about a specific command" << std::endl;

    }
}
