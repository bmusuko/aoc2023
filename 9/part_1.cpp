#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void printVector(const std::vector<long long>& vec) {
    std::cout << "Vector elements: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        std::string line;
        std::vector<std::vector<long long> > sensors;


        while (std::getline(file, line)) {
            std::vector<long long> newSensor;
            std::istringstream ss(line);
            std::string  _num;
            while(std::getline(ss, _num, ' ')) {
                if(!_num.empty()) {
                    newSensor.push_back(std::stoll(_num));
                }
            }
            sensors.push_back(newSensor);
        }

        for (int s=0; s < sensors.size(); s++) {
            std::vector<std::vector<long long> > pattern;
            int idx = 0;
            pattern.push_back(sensors[s]);
            printVector(sensors[s]);
            long long add = 0;
            while (true) {
                bool allZero = true;
                std::vector<long long> newPattern;
                for (int i=0;i<pattern[idx].size()-1; i++) {
                    int num = pattern[idx][i+1] - pattern[idx][i];
                    if (num != 0) {
                        allZero = false;
                    }
                    newPattern.push_back(num);
                }
                pattern.push_back(newPattern);
                idx++;
                printVector(newPattern);
                add += newPattern[newPattern.size() - 1];


                if (allZero) {
                    break;
                }
            }
            total += pattern[0][pattern[0].size()-1] + add;
            std::cout<<"====\n";
        }

        file.close();

        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}