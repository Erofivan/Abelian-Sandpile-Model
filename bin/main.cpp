#include "../lib/dynamic_structures.h"
#include "../lib/parser.h"
#include "../lib/helper.h"
#include "../lib/readfile.h"
#include "../lib/convertors.h"
#include "../lib/sandpile.h"


int main(int argc, char* argv[]) {
    // Filling list of valid commands
    unordered_map <string, string> valid_commands_list;
    FillValidCommandList(valid_commands_list);

    // Parcing command options into sctructure for further handling
    ArgValues arg_values; // Structure for containing argument values
    arg_values = Parser(argc, argv, valid_commands_list);

    if (argc == 1) {
        ErrorMessage(HelpCommandMustBeExecuted);
        return EXIT_FAILURE;
    }

    // Outout values if needed
    PreviewValues(arg_values);

    // Exit if error
    if (arg_values.input_path == nullptr) return EXIT_FAILURE;
    if (arg_values.output_path == nullptr) return EXIT_FAILURE;

    // Reading and getting coordinates
    vector<std::tuple<int, int, int>> starting_coordinates = 
                    ReadCoordinates(arg_values.input_path);

    // Saving pictures for iterations
    int total_iterations = arg_values.max_iter;
    if (arg_values.max_iter != 0) {
        // Initializing sandpile storage
        unordered_map<std::pair<int, int>, int> sediment; // Coords of all sand grands
        for (auto& i : starting_coordinates) {
            sediment[{std::get<0>(i), std::get<1>(i)}] = std::get<2>(i);
        }
        bool should_save = false;

        if (arg_values.freq != 0) {
            should_save = true;
        }

        //If we need to iterate with given frequency
        for (int i = 1; i <= total_iterations; ++i) {
            distribute_sand_by_iteration(sediment);
            
            if (should_save && ((i-1) % arg_values.freq == 0)) {
                ConverToBmp(sediment, arg_values.output_path, arg_values, i);
            }
        }

        //If need to save only last iteration
        if (!should_save && arg_values.max_iter) {
            ConverToBmp(sediment, arg_values.output_path, arg_values, arg_values.max_iter);
        }

    } else {
        // If we need to give just the last iteration
        distribute_sand(starting_coordinates);

        ConverToBmp(starting_coordinates, arg_values.output_path, arg_values);
    }

    return EXIT_SUCCESS;
}