#include "dynamic_structures.h"

std::ostream& operator<<(std::ostream& os, const string& str) {
    os << str.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, string& str) {
    char* buffer = new char [str.length+1];

    is >> buffer;

    delete [] str.data;

    str.length = 0;
    while (buffer[str.length] != '\0') {
        ++str.length;
    }
    str.data = new char[str.length + 1];
    for (size_t i = 0; i < str.length; ++i) {
        str.data[i] = buffer[i];
    }
    str.data[str.length] = '\0';
    delete [] buffer;
    return is;
}

std::istream& getline(std::istream& is, string& str) {
    delete[] str.data;
    str.data = nullptr;
    str.length = 0;

    char buffer[1024]; 
    is.getline(buffer, sizeof(buffer)); 

    str.length = 0;
    while (buffer[str.length] != '\0') {
        ++str.length;
    }

    str.data = new char[str.length + 1];
    for (size_t i = 0; i < str.length; ++i) {
        str.data[i] = buffer[i];
    }
    str.data[str.length] = '\0'; 

    return is;
}
