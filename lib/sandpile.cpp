#include "sandpile.h"

void distribute_sand_by_iteration(unordered_map<std::pair<int, int>, int>& sediment) {
    queue<std::pair<int, int>> changes;

    for (auto& entry : sediment) {
        if (entry.second >= 4) {
            changes.push(entry.first);
        }
    }

    unordered_map<std::pair<int, int>, int> changes_map;
    while (!changes.empty()) {
        std::pair<int, int> coord = changes.front();
        changes.pop();

        int sand_count = sediment[coord];
        if (sand_count >= 4) {
            int distribute_count = sand_count / 4;
            sediment[coord] -= distribute_count * 4;

            vector<std::pair<int, int>> neighbors = {
                std::make_pair(coord.first - 1, coord.second),
                std::make_pair(coord.first + 1, coord.second),
                std::make_pair(coord.first, coord.second - 1),
                std::make_pair(coord.first, coord.second + 1)
            };

            for (auto& neighbor : neighbors) {
                if (changes_map.count(neighbor) == 0) {
                    changes_map[neighbor] = 0; 
                }
                changes_map[neighbor] += distribute_count;
            }
        }
    }

    for (auto& entry : changes_map) {
        auto& neighbor = entry.first;
        int added_sand = entry.second;

        if (sediment.count(neighbor) == 0) {
            sediment[neighbor] = 0;
        }

        sediment[neighbor] += added_sand;
    }
}

void calculate_bounds(vector<std::tuple<int, int, int>>& sediment,
                      int& left_edge, int& right_edge, int& top_edge, int& bottom_edge) {
    const double ALPHA = 1;

    left_edge = std::numeric_limits<int>::max();
    right_edge = std::numeric_limits<int>::min();
    top_edge = std::numeric_limits<int>::min();
    bottom_edge = std::numeric_limits<int>::max();

    for (auto& entry : sediment) {
        int x = std::get<0>(entry);
        int y = std::get<1>(entry);
        int sand_count = std::get<2>(entry);

        if (sand_count == 0) continue;

        int radius = static_cast<int>(std::ceil(ALPHA * std::sqrt(sand_count)));

        left_edge = std::min(left_edge, x - radius);
        right_edge = std::max(right_edge, x + radius);
        top_edge = std::max(top_edge, y + radius);
        bottom_edge = std::min(bottom_edge, y - radius);
    }
}

void distribute_sand(vector<std::tuple<int, int, int>>& sediment) {
    int left_edge;
    int right_edge;
    int top_edge;
    int bottom_edge;
    calculate_bounds(sediment, left_edge, right_edge, top_edge, bottom_edge);

    int width = right_edge - left_edge + 1;
    int height = top_edge - bottom_edge + 1;

    int* field = new int[width * height]();
    bool* in_queue = new bool[width * height]();

    queue<int> changes;

    for (auto& entry : sediment) {
        int x = std::get<0>(entry) - left_edge;
        int y = std::get<1>(entry)  - bottom_edge;
        int index = y * width + x;
        field[index] = std::get<2>(entry);

        if (std::get<2>(entry) >= 4) {
            changes.push(index);
            in_queue[index] = true;
        }
    }

    const int dx[4] = {1, 0, -1, 0};
    const int dy[4] = {0, 1, 0, -1};

    while (!changes.empty()) {
        int current = changes.front();
        changes.pop();
        in_queue[current] = false;

        int y = current / width;
        int x = current % width;

        int sand_to_distribute = field[current] / 4;
        if (sand_to_distribute == 0) continue;

        field[current] %= 4;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                int neighbor = ny * width + nx;
                field[neighbor] += sand_to_distribute;

                if (field[neighbor] >= 4 && !in_queue[neighbor]) {
                    changes.push(neighbor);
                    in_queue[neighbor] = true;
                }
            }
        }
    }
    sediment.clear();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int value = field[i * width + j];
            if (value > 0) {
                sediment.push_back(std::make_tuple(j + left_edge, 
                                                   i + bottom_edge, value));
            }
        }
    }

    delete [] field;
    delete [] in_queue;
}
