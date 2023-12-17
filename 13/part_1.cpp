#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void printVector(const std::vector<std::string>& vec) {
    std::cout << "Vector elements: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

bool checkPalindrome(std::vector<std::string> pattern, int left, int right) {
    if (left < 0 || right >= pattern.size()) {
        return true;
    }
    return pattern[left] == pattern[right] && checkPalindrome(pattern, left-1, right+1);
}

int findReflection(std::vector<std::string> pattern) {
    for (int left = 0; left < pattern.size()-1; left++) {

        if (checkPalindrome(pattern, left, left+1)) {
            return left+1;
        }
    }
    return -1;
}

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        std::string line;

        std::vector<std::vector<std::string> > worlds;

        std::vector<std::string> world;
        while (std::getline(file, line)) {
            if (line.empty()) {
                worlds.push_back(world);
                world.clear();
            } else {
                world.push_back(line);
            }
        }
        worlds.push_back(world);


        for (std::vector<std::string> currWorld: worlds) {
//            printVector(currWorld);

            int horizontal = findReflection(currWorld);
            if (horizontal != -1) {
                total += horizontal * 100;
            } else {
                std::vector<std::string> verticalWorlds;

                int n = currWorld.size();
                int m = currWorld[0].size();


                for (int j = 0; j < m; j++) {
                    std::string temp = "";
                    for (int i = 0;i < n; i++) {
                        temp += currWorld[i][j];
                    }
                    verticalWorlds.push_back(temp);
                }

                total += findReflection(verticalWorlds);
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