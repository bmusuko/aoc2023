#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <cmath>
#include <unordered_map>

// Function to print a set
void printSet(const std::set<int>& s) {
    for (const int& value : s) {
        std::cout << value << " ";
    }
    std::cout << std::endl;  // Print a newline after printing all the set elements
}

void printMap(const std::unordered_map<int, int>& myMap) {
    for (const auto& pair : myMap) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
}


int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {
        std::string line;
        int total = 0;

        std::unordered_map<int, int> scratches;


        int card_idx = 1;
        while (std::getline(file, line)) {
            scratches[card_idx]++;
            int col_pos = line.find(':');
            std::string card_str = line.substr(col_pos+1);

            int guard_pos = card_str.find('|');



            std::set<int> card_set;
            std::string _num;
            std::istringstream ss(card_str.substr(0, guard_pos));


            while (std::getline(ss, _num, ' ')) {
                if (!_num.empty()) {
                    card_set.insert(atoi(_num.c_str()));
                }
            }

            std::istringstream sss(card_str.substr(guard_pos+1));
            int hit = 0;

            while (std::getline(sss, _num, ' ')) {
                if (!_num.empty() && card_set.count(atoi(_num.c_str())) > 0) {
                    hit++;
                }
            }


            for (int i = card_idx+1; i < card_idx+1+hit; i++) {
                scratches[i] += scratches[card_idx];
            }
            card_idx++;
        }

//        printMap(scratches);
        file.close();


        for (const auto& pair : scratches) {
            total += pair.second;
        }

        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}