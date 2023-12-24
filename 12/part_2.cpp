#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>


// Global variable declaration
std::unordered_map<std::string, long long> dp;


std::string getKey(std::string check, std::vector<long long> pattern) {
    std::string ans = check + "---";

    for (const auto& element: pattern) {
        ans += std::to_string(element) + ",";
    }
    return ans;

}

void printVector(const std::vector<long long>& vec) {
    std::cout << "Vector elements: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}


long long generateCombination(std::string check, std::vector<long long> pattern) {
    if (check == "") {
        if (pattern.size() > 0) {
            return 0;
        }
        return 1;
    }
    if (pattern.size() == 0) {
        if (check.find('#') != -1) {
            return 0;
        }
        return 1;
    }

    std::string key = getKey(check, pattern);
    if (dp.find(key) != dp.end()) {
        return dp[key];
    }


    long long result = 0;

    if (check[0] == '.' || check[0] == '?') {
        result += generateCombination(check.substr(1), pattern);
    }

    if (check[0] == '#' || check[0] == '?') {
        long long patternSize = pattern[0];

        if (patternSize > check.size()) {
            result += 0;
        } else  {
            if (check.substr(0, patternSize).find('.') != -1) {
                result += 0;
            } else {
                if (check.size() == patternSize) {
                    if (pattern.size() == 1) {
                        result += 1;
                    }
                } else {
                    if (check[patternSize] != '#') {
//                        std::cout << "lanjut\n";

                        std::vector<long long> nextPattern(pattern.begin()+1, pattern.end());
                        std::string newCheck = check.substr(patternSize+1);
                        result += generateCombination(newCheck, nextPattern);
                    }
                }
            }
        }

    }
    dp[key] = result;

    return result;
}

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        std::string line;

        while (std::getline(file, line)) {
            int space_col = line.find(' ');
            std::string spring = line.substr(0, space_col);
            std::string combination = line.substr(space_col+1);

            std::string _show;
            std::istringstream ss(combination);
            std::vector<long long> numbers;
            long long sum = 0;
            while(std::getline(ss, _show, ',')) {
                if (!_show.empty()) {
                    sum += std::stoll(_show);
                    numbers.push_back(std::stoll(_show));
                }
            }

            std::string newSpring = spring;
            for (int k=0;k<4;k++) {
                newSpring += "?" + spring;
            }

            std::vector<long long> newNumber = numbers;
            for (int k=0;k<4;k++) {
                for (int l = 0;l< numbers.size();l++) {
                    newNumber.push_back(numbers[l]);
                }
            }



            total += generateCombination(newSpring, newNumber);
        }

        file.close();

        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}