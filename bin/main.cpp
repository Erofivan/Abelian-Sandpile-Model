#include <iostream>
#include <fstream>

//begin Parcer

struct ArgValues{
    struct color {
        int zero = 0xFFFFFF;
        int two = 0x00FF00;
        int tree = 0xFF00FF;
        int four = 0xFFFF00;
        int five = 0x000000;
    };
    char* input_path = nullptr;
    char* output_path = nullptr;
    int max_iter = -1;
    int freq = -1;
    color colors;
};

void ProcessCommand(char* arg, ArgValues result) {
    int cnt = 1;
    while (arg[cnt] != '\0' && arg[cnt] != '=' && cnt <= 10) {
        ++cnt;
    }
    if (cnt > 10) {
        std::cerr << "error: unknown option" << std::endl; //later add excatly what argument is incorrect
        return;
    }
    char cmd[11] = {}; //11 is max length of an argument. later please rewrite
    for (int i = 0; i < cnt; ++i) {
        cmd[i] = arg[i];
    } 

}

void Parcer(int argc, char* argv[]) {
    ArgValues result;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            ProcessCommand(argv[i], result);
        }
    }
}
//end Parcer
int main(int argc, char* argv[]) {
    std::cout << "1";
}