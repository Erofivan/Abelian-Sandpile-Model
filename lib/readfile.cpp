#include "readfile.h"

vector<std::tuple<int, int, int>> ReadCoordinates(string& str) {
    const int kInputPathNameSize = str.size();
    char buffer[kInputPathNameSize + 1]; 
    memcpy(buffer, str.c_str(), kInputPathNameSize); 
    buffer[kInputPathNameSize] = '\0';
    const char* filename = buffer;

    std::ifstream fin(filename);

    if (!fin.is_open()) {
        std::ofstream fout(filename); 
        fout.close();
        fin.open(filename);
    }

    vector<std::tuple<int, int, int>> data;

    string line; 
    while (getline(fin, line)) { 
        std::istringstream ss(line.c_str());
        int x, y, grains;
        ss >> x >> y >> grains;

        if (ss) { 
            data.push_back(std::make_tuple(x, y, grains));
        }
    }

    fin.close();
    return data;
}
