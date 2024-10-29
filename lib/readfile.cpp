#include "readfile.h"

string itos(long long value) {
    if (value == 0) {
        static char buffer[2] = "0"; 
        return buffer;
    }
    char buffer[20];
    int index = 0;

    while (value > 0) {
        buffer[index++] = (value % 10) + '0'; 
        value /= 10; 
    }
    buffer[index] = '\0';

    for (int i = 0; i < index / 2; i++) {
        std::swap(buffer[i], buffer[index - i - 1]);
    }
    const char* temp = buffer;
    string res = temp;
    return res;
}

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
