#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <algorithm>


struct node {
    std::string left;
    std::string right;
};

// Function to calculate the GCD using Euclid's algorithm
long long calculateGCD(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the LCM of two numbers
long long calculateLCM(long long a, long long b) {
    return (a * b) / calculateGCD(a, b);
}

// Function to calculate the LCM of a vector of integers
long long calculateLCMVector(const std::vector<long long>& numbers) {
    long long result = 1;

    for (long long num : numbers) {
        result = calculateLCM(result, num);
    }

    return result;
}

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        std::vector<std::string> worlds;
        std::string line;
        std::unordered_map<std::string, node> mapper;
        std::string step;


        while (std::getline(file, line)) {
            worlds.push_back(line);
        }

        step = worlds[0];

        std::vector<std::string> curr;


        for (int i = 2; i < worlds.size(); i++) {
            node newNode = {worlds[i].substr(7, 3), worlds[i].substr(12, 3)};
            std:: string from = worlds[i].substr(0, 3);
            mapper[from] = newNode;

            if (from[2] == 'A') {
                curr.push_back(from);
            }
        }

        for (int i =0 ;i < curr.size(); i++) {
            std::cout<<curr[i]<<std::endl;
        }

        int idx = 0;

        std::vector<long long> distances;

        for (int i=0;i< curr.size(); i++) { // 0-5
            int distance = 0;
            int idx = 0;
            while (true) {
                distance++;
                if (step[idx] == 'L') {
                    curr[i] = mapper[curr[i]].left;
                } else {
                    curr[i] = mapper[curr[i]].right;
                }
                if (curr[i][2] == 'Z') {
                    distances.push_back(distance);
                    std::cout<<distance<<std::endl;
                    break;
                }
                idx = (idx + 1) % step.size();
            }
        }


        total = calculateLCMVector(distances);
        std::cout<<total<<std::endl;



        file.close();
    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}

// 262