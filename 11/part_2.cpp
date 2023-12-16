#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

struct point {
    long long x;
    long long y;
};

void printMatrix(const std::vector<std::vector<point> >& matrix) {
    for (const auto& row : matrix) {
        for (const point& ch : row) {
            std::cout <<"(" << ch.x <<"," << ch.y << ") ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        long long distance = 1000000;
        std::string line;
        std::vector<std::vector<char> > world; // extended row


        while (std::getline(file, line)) {
            std::vector<char> row;
            for (int i = 0; i<line.size();i++) {
                row.push_back(line[i]);
            }
            world.push_back(row);
        }


        std::vector<std::vector<point> > adder;
        // init
        for (int i = 0;i < world.size(); i++) {
            std::vector<point> row;
            for (int j = 0; j < world[0].size(); j++) {
                row.push_back({0,0});
            }
            adder.push_back(row);
        }


        // row
        for (int i=0; i < world.size(); i++) {
            bool isEmpty = true;
            for (int j=0;j< world[i].size();j++) {
                if (world[i][j] == '#') {
                    isEmpty = false;
                }
            }

            if (isEmpty) {
                for (int k=i+1; k < world.size();k++) {
                    for (int j = 0; j < world[k].size();j++) {
                        adder[k][j].x += distance-1;
                    }
                }
            }
        }


        // column
        for (int j=0; j < world[0].size();j++) {
            bool isEmpty = true;
            for (int i=0;i<world.size();i++) {
                if (world[i][j] == '#') {
                    isEmpty = false;
                }
            }

            if (isEmpty) {
                for (int i = 0; i< world.size();i++) {
                    for (int k=j+1; k < world[0].size();k++) {
                        adder[i][k].y += distance-1;
                    }
                }
            }

        }

        std::vector<point> points;

        for (int i = 0; i < world.size(); i++) {
            for (int j = 0; j < world[0].size(); j++) {
                if (world[i][j] == '#') {
                    point newPoint = {i + adder[i][j].x, j + adder[i][j].y};
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