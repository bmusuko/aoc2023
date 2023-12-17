#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct data {
    std::string label;
    int focal;
};

int getAsciiValue(char myChar) {
    return static_cast<int>(myChar);
}

int hashStr(std::string hash) {
    long long currValue = 0;

    for (char c: hash) {
        currValue += getAsciiValue(c);
        currValue *= 17;
        currValue %= 256;
    }
    return currValue;
}

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        std::string line;
        std::vector<std::string> hashes;


        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string _hash;
            while(std::getline(ss, _hash, ',')) {
                if(!_hash.empty()) {
                    hashes.push_back(_hash);
                }
            }
        }


        std::vector<std::vector<data> > boxes;
        for (int i =0;i<256;i++) {
            std::vector<data> emptyRow;
            boxes.push_back(emptyRow);
        }

        for (std::string hash: hashes) {
            bool isAdd = true;
            if (hash.find('-') != -1) {
                isAdd = false;
            }

            if (isAdd) {
                int equal_pos = hash.find('=');
                std::string label = hash.substr(0, equal_pos);
                int lenses = std::stoi(hash.substr(equal_pos+1));
                int box = hashStr(label);



                bool isFound = false;
                for (int i = 0; i< boxes[box].size() && !isFound; i++) {
                    if (boxes[box][i].label == label) {
                        boxes[box][i].focal = lenses;
                        isFound = true;
                    }
                }
                if (!isFound) {
                    boxes[box].push_back({label, lenses});
                }
            } else {
                int neg_pos = hash.find('-');
                std::string label = hash.substr(0, neg_pos);
                int box = hashStr(label);

                // Index variable
                int idx = 0;

                // Iterate through the vector using index
                while (idx < boxes[box].size()) {
                    // Check if the current element matches the element to be removed
                    if (boxes[box][idx].label == label) {
                        // Erase the element
                        boxes[box].erase(boxes[box].begin() + idx);
                    } else {
                        // Move to the next element
                        ++idx;
                    }
                }

            }

        }

        for (int i = 0; i< boxes.size(); i++) {
            for (int j = 0; j < boxes[i].size(); j++) {
                total += (i+1) * (j+1) * boxes[i][j].focal;
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