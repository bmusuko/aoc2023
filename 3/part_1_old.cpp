#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <unordered_map>
#include <set>



// find all number
// store (i,j) => num
// store (i,j) => sequence

// find all symbol
// check all direction
// if num check is sequence processed
// else add

void printMap(const std::unordered_map<std::string, int>& myMap) {
    for (const auto& pair : myMap) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
}

std::string getKey(int i, int j) {
    return std::to_string(i) + "#" + std::to_string(j);
}


int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {
        std::string line;
        int total = 0;
        std::vector<std::vector<char> > world;


        while (std::getline(file, line)) {
            std::vector<char> row;

            for (char c: line) {
                row.push_back(c);
            }
            world.push_back(row);
        }

        std::unordered_map<std::string, int> pointToNum;
        std::unordered_map<std::string, int> pointToSequence;
        // n x m size
        // n horizontal
        int n = world.size();
        // m vertical
        int m = world[0].size();

        int sequence = 1;

        for (int i = 0; i<n; i++) {
            int curr = 0;
            int length = 0;
            bool checking = false;
            for (int j = 0; j< m; j++) {
                char c = world[i][j];

                if (isdigit(c)) {
                    checking = true;
                    curr = (curr * 10) + (c - '0');
                    length += 1;
                } else {
                    if (checking) {
                        for (int k = (j - length); k < j; k++) {
                            pointToNum[getKey(i, k)] = curr;
                            pointToSequence[getKey(i, k)] = sequence;
                        }

                        // reset
                        checking = false;
                        length = 0;
                        curr = 0;
                        sequence++;
                    }
                }
            }

            if (checking) {
                for (int k = (m - length); k < m; k++) {
                    pointToNum[getKey(i, k)] = curr;
                    pointToSequence[getKey(i, k)] = sequence;
                }
            }
        }

        std::unordered_map<int, bool> used;
        printMap(pointToNum);


        for (int i = 0; i<n; i++) {
            for (int j = 0; j < m; j++) {
                char c = world[i][j];
                if (!isdigit(c) && c != '.') {
                    // check 8 direction
                    for (int x = i-1; x < i + 2; x++) {
                        for (int y = j-1; y < j + 2; y++) {
                            if (x >= 0 && x<n && y>=0 && y < m) {
                                std::string key = getKey(x,y);

                                if (pointToSequence[key] != 0 && !used[pointToSequence[key]]) {
                                    used[pointToSequence[key]] = true;
                                    total += pointToNum[key];
                                }

                            }
                        }
                    }
                }
            }
        }

        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}