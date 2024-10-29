#include "convertors.h"

void FillWithValues(std::string& str, std::string& dirname, 
                    pixel** pixels, int width, int height) {
    const int kInputPathNameSize = str.size();
    char buffer1[kInputPathNameSize + 1]; 
    memcpy(buffer1, str.c_str(), kInputPathNameSize); 
    buffer1[kInputPathNameSize] = '\0';
    const char* filename = buffer1;

    const int kInputDirNameSize = dirname.size();
    char buffer2[kInputDirNameSize + 1]; 
    memcpy(buffer2, dirname.c_str(), kInputDirNameSize); 
    buffer2[kInputDirNameSize] = '\0';
    const char* dname = buffer2;

    std::filesystem::path pictures_dir = std::filesystem::path(dname);
    if (!std::filesystem::exists(pictures_dir)) {
        std::filesystem::create_directory(pictures_dir);
    }
    
    std::filesystem::path full_path = pictures_dir / filename;

    std::ofstream picture(full_path.string(), std::ios::binary);

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

    uint8_t palette[20] = {
        255, 255, 255, 0,  
        0, 255, 0, 0,      
        128, 0, 128, 0,    
        255, 255, 0, 0,    
        0, 0, 0, 0         
    };
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
                 string& dirname, int name) {
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
    if (name != 0) output_picture = std::to_string(name) + ".bmp";
    else output_picture = std::to_string(total_grain_amount) + ".bmp";
    FillWithValues(output_picture, dirname, pixels, width, height);

    for (int i = 0; i < height; ++i) {
        delete[] pixels[i];
    }
    delete[] pixels;
}