#include "convertors.h"

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

void FillPalette(uint8_t palette[], ArgValues arg_values, int size) {
    string str = arg_values.palette;
    if (arg_values.palette == nullptr && !(arg_values.palette == "random")) {
        str = "FFFFFF,00FF00,800080,FFFF00,000000";
    }
    int minus = 28;
    for (int i = 18; i >= -1; --i) {
        if (i % 4 == 3) {
            minus -= 13;
            continue;
        }
        char c = str[minus];
        int value;
        if ('A' <= c && c <= 'F') {
            value = static_cast<int>(c-'A'+10);
        } else {
            value = static_cast<int>(c-'0');
        }
        ++minus;
        palette[i] = value*16;
        c = str[minus];
        if ('A' <= c && c <= 'F') {
            value = static_cast<int>(c-'A'+10);
        } else {
            value = static_cast<int>(c-'0');
        }
        palette[i] += value;
        minus++;
    }
    palette[3] = 0;
    palette[7] = 0;
    palette[11] = 0;
    palette[15] = 0;
    palette[19] = 0;
}

void FillWithValues(string& str, string& dirname, 
                pixel** pixels, int width, int height, ArgValues arg_values) {
    const int kInputPathNameSize = str.size();
    char* buffer1 = new char[kInputPathNameSize + 1]; 
    memcpy(buffer1, str.c_str(), kInputPathNameSize); 
    buffer1[kInputPathNameSize] = '\0';
    const char* filename = buffer1;

    const int kInputDirNameSize = dirname.size();
    char* buffer2 = new char [kInputDirNameSize + 1]; 
    memcpy(buffer2, dirname.c_str(), kInputDirNameSize); 
    buffer2[kInputDirNameSize] = '\0';
    const char* dname = buffer2;

    std::filesystem::path pictures_dir = std::filesystem::path(dname);
    if (!std::filesystem::exists(pictures_dir)) {
        std::filesystem::create_directory(pictures_dir);
    }
    
    std::filesystem::path full_path = pictures_dir / filename;

    std::ofstream picture(full_path.string(), std::ios::binary);

    delete [] buffer1;
    delete [] buffer2;
    uint8_t bmp_header[54] = {
        'B', 'M',            
        0, 0, 0, 0,          
        0, 0, 0, 0,          
        54 + 20, 0, 0, 0,         
        40, 0, 0, 0,         
        0, 0, 0, 0,          
        0, 0, 0, 0,          
        1, 0,                 
        4, 0,                 
        0, 0, 0, 0,          
        0, 0, 0, 0,          
        0, 0, 0, 0,          
        0, 0, 0, 0,          
        5, 0, 0, 0,          
        0, 0, 0, 0         
    };

    *reinterpret_cast<int*>(&bmp_header[18]) = width;
    *reinterpret_cast<int*>(&bmp_header[22]) = height;

    int row_size = ((width + 1) / 2 + 3) & ~3;
    int bmp_size = 54 + 20 + row_size * height;
    *reinterpret_cast<int*>(&bmp_header[2]) = bmp_size;

    picture.write(reinterpret_cast<char*>(bmp_header), sizeof(bmp_header));


    uint8_t palette[20];
    FillPalette(palette, arg_values);

    picture.write(reinterpret_cast<char*>(palette), sizeof(palette));

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; x += 2) {
            uint8_t byte = 0;
            if (x < width) {
                byte |= (pixels[y][x].value & 0x0F) << 4;
            }
            if (x + 1 < width) {
                byte |= (pixels[y][x + 1].value & 0x0F);
            }
            picture.put(byte);
        }
        
        for (int padding = 0; padding < (row_size - (width + 1) / 2); ++padding) {
            picture.put(0);
        }
    }

    picture.close();
}


void ConverToBmp(unordered_map<std::pair<int, int>, int>& sediment,
                 string& dirname, ArgValues arg_values, int name) {
    vector<std::tuple<int, int, int>> data;
    int min_x = std::numeric_limits<int>::max();
    int max_x = std::numeric_limits<int>::min();
    int min_y = std::numeric_limits<int>::max();
    int max_y = std::numeric_limits<int>::min();

    long long total_grain_amount = 0;
    for (const auto& i : sediment) { 
        int x = i.first.first;
        int y = i.first.second;
        int grains = i.second;
        total_grain_amount += grains;

        data.push_back(std::make_tuple(x, y, grains));
        min_x = std::min(min_x, x);
        max_x = std::max(max_x, x);
        min_y = std::min(min_y, y);
        max_y = std::max(max_y, y);
    }

    int width = max_x - min_x + 1;
    int height = max_y - min_y + 1;

    pixel** pixels = new pixel* [height];
    for (int i = 0; i < height; ++i) {
        pixels[i] = new pixel[width]();
    }

    for (const auto& i : data) {
        int x = std::get<0>(i);
        int y = std::get<1>(i);
        int code = std::get<2>(i);

        int xPos = x - min_x;
        int yPos = y - min_y;
        switch (code) {
            case 0: pixels[height - 1 - yPos][xPos].value = 0; break;
            case 1: pixels[height - 1 - yPos][xPos].value = 1; break;
            case 2: pixels[height - 1 - yPos][xPos].value = 2; break;
            case 3: pixels[height - 1 - yPos][xPos].value = 3; break;
            default: pixels[height - 1 - yPos][xPos].value = 4; break;
        }
    }

    string output_picture;
    if (name != 0) output_picture = itos(name) + ".bmp";
    else output_picture = itos(total_grain_amount) + ".bmp";
    FillWithValues(output_picture, dirname, pixels, width, height, arg_values);

    for (int i = 0; i < height; ++i) {
        delete[] pixels[i];
    }
    delete[] pixels;
}

void ConverToBmp(vector<std::tuple<int, int, int>>& data,
                 string& dirname, ArgValues arg_values, int name) {
    int min_x = std::numeric_limits<int>::max();
    int max_x = std::numeric_limits<int>::min();
    int min_y = std::numeric_limits<int>::max();
    int max_y = std::numeric_limits<int>::min();

    long long total_grain_amount = 0;
    for (auto& i : data) { 
        int x = std::get<0>(i);
        int y = std::get<1>(i);
        int grains = std::get<2>(i);
        total_grain_amount += grains;

        min_x = std::min(min_x, x);
        max_x = std::max(max_x, x);
        min_y = std::min(min_y, y);
        max_y = std::max(max_y, y);
    }

    int width = max_x - min_x + 1;
    int height = max_y - min_y + 1;

    pixel** pixels = new pixel* [height];
    for (int i = 0; i < height; ++i) {
        pixels[i] = new pixel[width]();
    }

    for (const auto& i : data) {
        int x = std::get<0>(i);
        int y = std::get<1>(i);
        int code = std::get<2>(i);

        int xPos = x - min_x;
        int yPos = y - min_y;
        switch (code) {
            case 0: pixels[height - 1 - yPos][xPos].value = 0; break;
            case 1: pixels[height - 1 - yPos][xPos].value = 1; break;
            case 2: pixels[height - 1 - yPos][xPos].value = 2; break;
            case 3: pixels[height - 1 - yPos][xPos].value = 3; break;
            default: pixels[height - 1 - yPos][xPos].value = 4; break;
        }
    }

    string output_picture;
    if (name != 0) output_picture = itos(name) + ".bmp";
    else output_picture = itos(total_grain_amount) + ".bmp";
    FillWithValues(output_picture, dirname, pixels, width, height, arg_values);

    for (int i = 0; i < height; ++i) {
        delete[] pixels[i];
    }
    delete[] pixels;
}
