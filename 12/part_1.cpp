#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

void printVector(const std::vector<long long>& vec) {
    std::cout << "Vector elements: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}


bool checkCombination(std::string check, std::vector<long long> pattern) {
    int hit = pattern.size();
    int i = 0;

    std::string _show;
    std::istringstream ss(check);
    std::vector<long long> numbers;
    while(std::getline(ss, _show, '.') && hit >= 0) {
        if (!_show.empty()) {
            if (_show.size() == pattern[i]) {
                hit--;
                i++;
            } else {
                return false;
            }
        }
    }
    return hit == 0;
}

long long generateCombination(std::string check, std::vector<long long> pattern, int idx) {
    if (idx == check.size()) {
        std::replace(check.begin(), check.end(), '?', '.');
        if (checkCombination(check, pattern)) {
            return 1;
        } else {
            return 0;
        }
    }
    if (check[idx] != '?') {
        return generateCombination(check, pattern, idx+1);
    }
    // skip
    long long skipCount = generateCombination(check, pattern, idx+1);
    // replace
    check[idx] = '#';
    long long replaceCount = generateCombination(check, pattern, idx+1);
    return skipCount + replaceCount;
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
//            printVector(numbers);
//            std::cout<<spring<<"\n"<<sum<<"\n\n";
            total += generateCombination(spring, numbers, 0);
        }

        file.close();

        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}