#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <cmath>
#include <unordered_map>

struct node {
    std::string left;
    std::string right;
};

void printMapper(const std::unordered_map<std::string, node>& mapper) {
    for (const auto& entry : mapper) {
        const std::string& key = entry.first;
        const node& value = entry.second;

        std::cout << "Key: " << key << " | Left: " << value.left << " | Right: " << value.right << std::endl;
    }
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

        for (int i = 2; i < worlds.size(); i++) {
            node newNode = {worlds[i].substr(7, 3), worlds[i].substr(12, 3)};
            std:: string from = worlds[i].substr(0, 3);
            mapper[from] = newNode;
        }
//        printMapper(mapper);

        std::string curr = "AAA";
        int idx = 0;


        while (curr != "ZZZ") {
            if (step[idx] == 'L') {
                curr = mapper[curr].left;
            } else {
                curr = mapper[curr].right;
            }


            total += 1;
            idx = (idx + 1) % step.size();
        }



        file.close();

        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}