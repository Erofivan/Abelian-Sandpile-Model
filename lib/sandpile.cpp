#include "sandpile.h"

void hilbert(int n, int x, int y, 
              int xi, int xj, 
              int yi, int yj, 
              std::vector<std::pair<int, int>>& points) {
    if (n <= 0) return;
    hilbert(n-1, x, y, yi/2, yj/2, xi/2, xj/2, points);
    points.push_back({x + xi/2, y + yi/2});
    hilbert(n-1, x + xi/2, y + yi/2, xi/2, xj/2, yi/2, yj/2, points);
    points.push_back({x + xi/2 + xj/2, y + yi/2 + yj/2});
    hilbert(n-1, x+xi/2 + xj/2, y+yi/2+yj/2, xi/2, xj/2, yi/2, yj/2, points);
    points.push_back({x + xi + xj/2, y + yi + yj/2});
    hilbert(n-1, x+xi+xj/2, y+yi + yj/2, -yi/2, -yj/2, -xi/2, -xj/2, points);
}

std::vector<std::pair<int, int>> generate_hilbert_curve(int order) {
    std::vector<std::pair<int, int>> points;
    hilbert(order, 0, 0, 1 << (order-1), 0, 0, 1 << (order-1), points);
    return points;
}

void distribute_sand_by_iteration(std::unordered_map<std::pair<int, int>, int>& sediment) {
    std::queue<std::pair<int, int>> changes;

    for (auto& entry : sediment) {
        if (entry.second >= 4) {
            changes.push(entry.first);
        }
    }

    std::unordered_map<std::pair<int, int>, int> changes_map;
    while (!changes.empty()) {
        std::pair<int, int> coord = changes.front();
        changes.pop();

        int sand_count = sediment[coord];
        if (sand_count >= 4) {
            int distribute_count = sand_count / 4;
            sediment[coord] -= distribute_count * 4;

            std::vector<std::pair<int, int>> neighbors = {
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

void distribute_sand(std::unordered_map<std::pair<int, int>, int>& sediment) {
    std::queue<std::pair<int, int>> changes;

    for (auto& entry : sediment) {
        if (entry.second >= 4) {
            changes.push(entry.first);
        }
    }

    std::vector<std::pair<int, int>> neighbors = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    while (!changes.empty()) {
        auto coord = changes.front();
        changes.pop();

        int sand_count = sediment[coord];

        if (sand_count >= 4) {
            int distribute_count = sand_count / 4;
            sediment[coord] -= distribute_count * 4;

            for (const auto& offset : neighbors) {
                std::pair<int, int> neighbor = {coord.first + offset.first, coord.second + offset.second};

                if (sediment.count(neighbor) == 0) {
                    sediment[neighbor] = 0;
                }

                sediment[neighbor] += distribute_count;

                if (sediment[neighbor] >= 4) {
                    changes.push(neighbor);
                }
            }
        }
    }
}
