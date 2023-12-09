#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <cmath>

void printVector(const std::vector<long long>& vec) {
    std::cout << "Vector elements: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}


int main() {
    std::ifstream file("input2.txt");

    if (file.is_open()) {
        std::string line;
        std::vector<std::string> world;
        long long total = 1;

        while (std::getline(file, line)) {
            world.push_back(line);
        }
        file.close();


        std::vector<long long> times;
        int col_pos = world[0].find(':');
        std::string _num;
        std::istringstream ss(world[0].substr(col_pos+2));

        while (std::getline(ss, _num, ' ')) {
            if (!_num.empty()) {
                times.push_back(std::stoll(_num));
            }
        }

        std::vector<long long> distances;
        col_pos = world[1].find(':');
        std::istringstream sss(world[1].substr(col_pos+2));

        while (std::getline(sss, _num, ' ')) {
            if (!_num.empty()) {
                distances.push_back(std::stoll(_num));
            }
        }

        printVector(times);
        printVector(distances);


        for (long long i = 0; i < times.size(); i++) {
            long long time = times[i];
            long long distance = distances[i];

            long long hit = 0;
            for (long long k = 1; k < time; k++) {
                long long currDistance = (time-k) * k;
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