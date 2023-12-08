#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include <cmath>
#include <vector>

struct mapper {
    long long from;
    long long destination;
    long long range;
};


// Function to print a set
void printSet(const std::set<long long>& s) {
    for (const long long& value : s) {
        std::cout << value << " ";
    }
    std::cout << std::endl;  // Print a newline after printing all the set elements
}

int main() {
    std::ifstream file("input.txt");


    if (file.is_open()) {
        std::string line;
        std::vector<std::string> world;
        long long total = 0;

        std::set<long long> seeds;

        while (std::getline(file, line)) {
            world.push_back(line);
        }

        // get first seeds
        int col_pos = world[0].find(':');
        std::string _num;
        std::istringstream ss(world[0].substr(col_pos+2));

        std::vector<long long> seed_temp;

        while (std::getline(ss, _num, ' ')) {
            if (!_num.empty()) {
                seed_temp.push_back(std::stoll(_num));
            }
        }

        for (int i = 0; i < seed_temp.size(); i += 2) {
            for (int k = 0; k < seed_temp[i+1]; k++) {
                seeds.insert(seed_temp[i] +k);
            }
        }

//        printSet(seeds);

        std::vector<std::vector<mapper> > mappers;
        std::vector<mapper> currMapper;
        int idx = 0;
        for (int i = 1; i< world.size(); i++) {
            line = world[i];
            if (line.empty()) {
                continue;
            }

            if (line.find(':') != -1) {
                if (idx != 0) {
                    mappers.push_back(currMapper);
                }
                currMapper.clear();
                idx++;
                continue;
            }

            std::istringstream sss(line);
            std::vector<long long> temp;
            while (std::getline(sss, _num, ' ')) {
                if (!_num.empty()) {
                    temp.push_back(std::stoll(_num));
                }
            }

            mapper newMapper = {temp[0], temp[1], temp[2]};
            currMapper.push_back(newMapper);
        }
        mappers.push_back(currMapper);

        for (int i = 0; i< mappers.size();i++) {
            std::set<long long> newSeeds;

            for (const long long& seed : seeds) {
                bool hit = false;

                for (int k =0; k<mappers[i].size(); k++) {
                    if (seed >= mappers[i][k].destination && seed < mappers[i][k].destination + mappers[i][k].range) {
                        hit = true;
                        newSeeds.insert(mappers[i][k].from + (seed - mappers[i][k].destination));
                    }
                }
                if (!hit) {
                    newSeeds.insert(seed);
                }

            }
//            std::cout<<i<<std::endl;
//            printSet(newSeeds);
//            std::cout<<"===="<<std::endl;
            total = *newSeeds.begin();
            seeds = newSeeds;
        }





        file.close();
        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}