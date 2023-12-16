#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

struct point {
    int x;
    int y;
};

void printMatrix(const std::vector<std::vector<char> >& matrix) {
    for (const auto& row : matrix) {
        for (const char& ch : row) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        std::string line;
        std::vector<std::string> world_temp; // extended row


        while (std::getline(file, line)) {
            world_temp.push_back(line);
            if (line.find('#') == -1) {
                world_temp.push_back(line);
            }
        }

        std::vector<std::vector<char> > world;
        for (int i = 0; i < world_temp.size(); i++) {
            std::vector<char> emptyRow;
            world.push_back(emptyRow);
        }

        for (int j = 0; j < world_temp[0].size(); j++) {
            bool isEmpty = true;
            for (int i = 0; i < world_temp.size(); i++) {
                world[i].push_back(world_temp[i][j]);
                if (world_temp[i][j] != '.') {
                    isEmpty = false;
                }
            }

            if (isEmpty) {
                for (int i = 0; i < world_temp.size(); i++) {
                    world[i].push_back('.');
                }
            }
        }

        std::vector<point> points;

        for (int i = 0; i < world.size(); i++) {
            for (int j = 0; j < world[0].size(); j++) {
                if (world[i][j] == '#') {
                    point newPoint = {i, j};
                    points.push_back(newPoint);
                }
            }
        }

        for (int i = 0; i < points.size()-1; i++) {
            for (int j = i+1; j < points.size(); j++) {
                total += std::abs(points[i].x - points[j].x) + std::abs(points[i].y - points[j].y);
            }
        }


        file.close();

        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}