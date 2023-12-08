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

        // n x m size
        // n horizontal
        int n = world.size();
        // m vertical
        int m = world[0].size();

        std::unordered_map<std::string, std::vector<int> > star;

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
                        std::unordered_map<std::string, bool> visited;
                        for (int k = (j - length); k < j; k++) {
                            // check 8 direction
                            for (int x = i - 1; x < i + 2; x++) {
                                for (int y = k - 1; y < k + 2; y++) {
                                    if (x >= 0 && x < n && y >= 0 && y < m) {
                                        if (visited[getKey(x,y)]) {
                                            continue;
                                        }
                                        visited[getKey(x,y)] = true;
                                        if (world[x][y] == '*') {
                                            star[getKey(x,y)].push_back(curr);
                                        }
                                    }
                                }
                            }


                        }

                        // reset
                        checking = false;
                        length = 0;
                        curr = 0;
                    }
                }
            }

            if (checking) {
                std::unordered_map<std::string, bool> visited;

                for (int k = (m - length); k < m; k++) {
                    // check 8 direction
                    for (int x = i - 1; x < i + 2; x++) {
                        for (int y = k - 1; y < k + 2; y++) {
                            if (x >= 0 && x < n && y >= 0 && y < m) {
                                if (visited[getKey(x,y)]) {
                                    continue;
                                }
                                visited[getKey(x,y)] = true;
                                if (world[x][y] == '*') {
                                    star[getKey(x,y)].push_back(curr);
                                }
                            }
                        }
                    }
                }
            }
        }

        for (const auto& pair : star) {
            if (pair.second.size() == 2) {
                total += pair.second[0] * pair.second[1];
            }
        }

        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}