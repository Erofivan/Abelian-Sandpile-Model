#include "../lib/dynamic_structures.h"
#include "../lib/parser.h"
#include "../lib/helper.h"
#include "../lib/readfile.h"
#include "../lib/convertors.h"
#include "../lib/sandpile.h"


int main(int argc, char* argv[]) {
    
    // int argc = 3;
    // char* argv[] = {"", "--input=input.tsv", "--output=pictures"};
    // Creating and filling of an unordered map, containing all valid options
    unordered_map <string, string> valid_commands_list;
    FillValidCommandList(valid_commands_list);

    // Parcing command options into sctructure for further handling
    ArgValues arg_values; // Structure for containing argument values
    arg_values = Parser(argc, argv, valid_commands_list);

    // Outout values if needed
    PreviewValues(arg_values);

    // Exit if error
    if (arg_values.input_path == nullptr) return EXIT_FAILURE;
    if (arg_values.output_path == nullptr) return EXIT_FAILURE;

    // Reading and getting coordinates
    vector<std::tuple<int, int, int>> starting_coordinates = 
                    ReadCoordinates(arg_values.input_path);

    // Preparing for proccseing all the coordinates
    int hilbert_curve_order = 5; //order of default hilbert curve
    int total_iterations = arg_values.max_iter;

    // Initializing sandpile storage
    unordered_map<std::pair<int, int>, int> sediment; //coords of all sand grands
    for (auto& i : starting_coordinates) {
        sediment[{std::get<0>(i), std::get<1>(i)}] = std::get<2>(i);
    }
    
    // Filling and processing gilbert order curve
    vector<std::pair<int, int>> hilbert_order = 
                                generate_hilbert_curve(hilbert_curve_order);

    // Saving pictures for iterations
    if (arg_values.max_iter != 0) {
        bool flag = false;

        if (arg_values.freq != 0) {
            flag = true;
        }

        for (int i = 1; i <= total_iterations; ++i) {
            distribute_sand_by_iteration(sediment);
            
            if (flag && ((i-1) % arg_values.freq == 0)) {
                ConverToBmp(sediment, arg_values.output_path, i);
            }
        }

        if (!flag && arg_values.max_iter) {
            ConverToBmp(sediment, arg_values.output_path, arg_values.max_iter);
        }

    } else {
        distribute_sand(sediment);

        ConverToBmp(sediment, arg_values.output_path);
    }

    return EXIT_SUCCESS;
}