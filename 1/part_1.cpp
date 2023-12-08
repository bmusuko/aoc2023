#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {
        std::string line;
        int total;

        while (std::getline(file, line)) {
            int num;

            for (int i = 0; i < line.size(); i++) {
                if (isdigit(line[i])) {
                    num = (line[i] - '0') * 10;
                    break;
                }
            }

            for (int i = line.size()-1; i >= 0; i--) {
                if (isdigit(line[i])) {
                    num += line[i] - '0';
                    break;
                }
            }

            total += num;
        }
        std::cout << total << std::endl;
        file.close();
    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}