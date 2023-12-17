#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>


void printMatrix(std::vector<std::vector<char> >& world) {
    for (const auto& row : world) {
        for (const char& ch : row) {
            std::cout << ch << "";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

}

std::string flatMatrix(std::vector<std::vector<char> >& world) {
    std::string flatWorld;

    for (const auto& row : world) {
        flatWorld += std::string(row.begin(), row.end()) + '*';
    }
    return flatWorld;
}

void tiltMatrix(std::vector<std::vector<char> >& world, int direction) {
    int n = world.size();
    int m = world[0].size();


    // 1 north
    // 2 west
    // 3 south
    // 4 east
    if (direction == 1) {
        for (int j = 0; j< m; j++) {
            int idx = 0;
            for (int i = 0; i < n; i++) {
                if (world[i][j] == 'O') {
                    world[i][j] = '.';
                    world[idx][j] = 'O';
                    idx++;
                } else if (world[i][j] == '#') {
                    idx = i+1;
                }
            }
        }
    } else if (direction == 2) {
        for (int i = 0; i < n;i++) {
            int idx = 0;
            for (int j = 0; j < m; j++) {
                if (world[i][j] == 'O') {
                    world[i][j] = '.';
                    world[i][idx] = 'O';
                    idx++;
                } else if (world[i][j] == '#') {
                    idx = j+1;
                }
            }
        }
    } else if (direction == 3) {
        for (int j = 0; j < m; j++) {
            int idx = n-1;
            for (int i = n-1; i >= 0; i--) {
                if (world[i][j] == 'O') {
                    world[i][j] = '.';
                    world[idx][j] = 'O';
                    idx--;
                } else if (world[i][j] == '#') {
                    idx = i-1;
                }
            }
        }
    } else if (direction == 4) {
        for (int i = 0; i < n; i++) {
            int idx = m-1;
            for (int j = m-1; j >= 0;j--) {
                if (world[i][j] == 'O') {
                    world[i][j] = '.';
                    world[i][idx] = 'O';
                    idx--;
                } else if (world[i][j] == '#') {
                    idx = j-1;
                }
            }
        }
    }
}


long long findSupport(std::vector<std::vector<char> >& world) {
    long long total = 0;
    int n = world.size();
    int m = world[0].size();
    for (int j = 0; j< m; j++) {
        for (int i = 0; i < n; i++) {
            if (world[i][j] == 'O') {
                total += (n-i);
            }
        }
    }
    return total;
}

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        long long rotation = 1000000000;
        std::string line;

        std::unordered_map<std::string, int> seen;


        std::vector<std::vector<char> > world;
        while (std::getline(file, line)) {
            std::vector<char> row;
            for (char c: line) {
                row.push_back(c);
            }
            world.push_back(row);
        }


        bool isMatched = false;
        bool firstHit = false;
        int target = -1;


        for (int k = 1; k<= rotation && !isMatched; k++) {
            for (int l = 1; l <=4; l++) {
                tiltMatrix(world, l);
            }
            std::string flatWorld = flatMatrix(world);
            if (seen[flatWorld] != 0) {
                if (!firstHit) {
                    int cycle = k-seen[flatWorld];
                    int pad = seen[flatWorld];
                    firstHit = true;
                    target = (((rotation - pad) % cycle) + pad);
                    std::cout<<seen[flatWorld]<<": "<<k<<std::endl;
                    std::cout<<"cycle length: "<<k-seen[flatWorld]<<std::endl;
                    std::cout<<"pad: "<<seen[flatWorld]<<std::endl;
                    std::cout<<"target:"<<target<<std::endl;

                }

                if (target == seen[flatWorld]) {
                    isMatched = true;
                }
            } else {
                seen[flatWorld] = k;
            }
        }
        total = findSupport(world);



        file.close();

        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}