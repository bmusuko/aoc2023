#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        std::string line;


        std::vector<std::string> world;
        while (std::getline(file, line)) {
            world.push_back(line);
        }

        int n = world.size();
        int m = world[0].size();
        for (int j = 0; j< m; j++) {
            int top = n;
            for (int i = 0; i < n; i++) {
                if (world[i][j] == 'O') {
                    total += top;
                    top--;
                } else if (world[i][j] == '#') {
                    top = (n-i)-1;
                }
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