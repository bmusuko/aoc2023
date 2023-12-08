#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int isNumberWord(std::string line, int idx, bool isReverse) {
    const std::string numbers[10] = {
            "one",
            "two",
            "three",
            "four",
            "five",
            "six",
            "seven",
            "eight",
            "nine"
    };

    for (int k = 0; k < 9; k++) {
        std::string num = numbers[k];

        int hit_left = num.size();
        if (isReverse) {
            int j = num.size()-1;
            for (int i = idx; i >= 0 && hit_left >= 0; i--) {
                if (line[i] == num[j]) {
                    hit_left--;
                } else {
                    break;
                }
                j--;
            }
        } else {
            int j = 0;
            for (int i = idx; i < line.size() && hit_left >= 0; i++) {
                if (line[i] == num[j]) {
                    hit_left--;
                } else {
                    break;
                }
                j++;
            }
        }


        if (hit_left == 0) {
            return (k+1);
        }
    }
    return -1;
}

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {
        std::string line;
        int total = 0;

        while (std::getline(file, line)) {
            int num;
            int first;
            int last;

            for (int i = 0; i < line.size(); i++) {
                if (isdigit(line[i])) {
                    first = line[i] - '0';
                    break;
                } else {
                    first = isNumberWord(line, i, false);
                    if (first != -1) {
                        break;
                    }
                }
            }

            for (int i = line.size()-1; i >= 0; i--) {
                if (isdigit(line[i])) {
                    last = line[i] - '0';
                    break;
                } else {
                    last = isNumberWord(line, i, true);
                    if (last != -1) {
                        break;
                    }
                }
            }
            num = (first * 10) + last;
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