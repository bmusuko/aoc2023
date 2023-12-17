#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


int getAsciiValue(char myChar) {
    return static_cast<int>(myChar);
}

int main() {
    std::ifstream file("test.txt");

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

        for (std::string hash: hashes) {
            long long currValue = 0;

            for (char c: hash) {
                currValue += getAsciiValue(c);
                currValue *= 17;
                currValue %= 256;
            }

            std::cout<<hash<<": "<<currValue<<"\n";
            total += currValue;
        }


        file.close();

        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}