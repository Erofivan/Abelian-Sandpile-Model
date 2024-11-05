#pragma once

#include <iostream>

#include "dynamic_structures.h"
#include "parser.h"

enum ErrorCode{
    InputPathWasNotProvided,
    OutputPathWasNotProvided,
    HelpCommandMustBeExecuted
};

void ErrorMessage(size_t ErrorCode = 0);
void PreviewValues(ArgValues& arg_values);