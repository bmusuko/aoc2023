#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <cmath>

void printVector(const std::vector<int>& vec) {
    std::cout << "Vector elements: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}


int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {
        std::string line;
        std::vector<std::string> world;
        int total = 1;

        while (std::getline(file, line)) {
            world.push_back(line);
        }
        file.close();


        std::vector<int> times;
        int col_pos = world[0].find(':');
        std::string _num;
        std::istringstream ss(world[0].substr(col_pos+2));

        while (std::getline(ss, _num, ' ')) {
            if (!_num.empty()) {
                times.push_back(std::stoi(_num));
            }
        }

        std::vector<int> distances;
        col_pos = world[1].find(':');
        std::istringstream sss(world[1].substr(col_pos+2));

        while (std::getline(sss, _num, ' ')) {
            if (!_num.empty()) {
                distances.push_back(std::stoi(_num));
            }
        }

        printVector(times);
        printVector(distances);


        for (int i = 0; i < times.size(); i++) {
            int time = times[i];
            int distance = distances[i];

            int hit = 0;
            for (int k = 1; k < time; k++) {
                int currDistance = (time-k) * k;
                if (currDistance > distance) {
                    hit += 1;
                }
            }

            total *= hit;
        }




        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}