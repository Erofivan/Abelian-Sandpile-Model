#include "helper.h"

void ErrorMessage(size_t ErrorCode = 0) {
    switch(ErrorCode) {
        case 0: {
            std::cerr << "error: input path was not provided" << std::endl;
            break;
        }
        case 1: {
            std::cerr << "error: output path was not provided" << std::endl;
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
    std::cout << "Input path: " << arg_values.input_path << std::endl;
    std::cout << "Outputh path: " << arg_values.output_path << std::endl;
    std::cout << "Max iter: " << arg_values.max_iter << std::endl;
    std::cout << "Freq: " << arg_values.freq << std::endl;
}
