#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct input {
    char move;
    int length;
    std::string color;
};

std::vector<std::vector<char> > world;

void printMatrix(const std::vector<std::vector<char> >& matrix) {
    for (const auto& row : matrix) {
        for (const char& ch : row) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }
}

void floodFill(int x, int y) {
    if (x < 0 || x >= world.size() || y < 0 || y >= world[0].size()) {
        return;
    }

    if (world[x][y] == '#') {
        return;
    }

    world[x][y] = '#';
    floodFill(x-1,y);
    floodFill(x+1,y);
    floodFill(x,y-1);
    floodFill(x,y+1);
}


int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        std::string line;
        std::vector<input> inputs; // extended row



        while (std::getline(file, line)) {
            int open_bracket_pos = line.find('(');
            int length = std::stoi(line.substr(2, open_bracket_pos - 3));
            std::string color = line.substr(open_bracket_pos+1, 7);
            inputs.push_back({line[0], length, color});
        }

        int n = 0;
        int m = 0;
        int left, right, top, bottom;
        int currX, currY;


        for (int i=0;i<inputs.size();i++) {
            input curr = inputs[i];

            if (curr.move == 'R') {
                currX += curr.length;
            } else if (curr.move == 'L') {
                currX -= curr.length;
            } else if (curr.move == 'U') {
                currY -= curr.length;
            } else if (curr.move == 'D') {
                currY += curr.length;
            }

            left = std::min(currX, left);
            right = std::max(currX, right);
            top = std::min(currY, top);
            bottom = std::max(currY, bottom);
        }

        std::cout<<"left: "<<left<<"\n";
        std::cout<<"right: "<<right<<"\n";
        std::cout<<"top: "<<top<<"\n";
        std::cout<<"bottom: "<<bottom<<"\n";


        n = (bottom - top ) + 1;
        m = (right - left) + 1;

        std::cout<<"n: "<<n<<"\n";
        std::cout<<"m: "<<m<<"\n";


        for (int i = 0; i < n; i++) {
            std::vector<char> row;
            for (int j = 0; j< m;j++) {
                row.push_back('.');
            }
            world.push_back(row);
        }



        for (int i=0;i<inputs.size();i++) {
            input curr = inputs[i];

            if (curr.move == 'R') {
                currX += curr.length;
            } else if (curr.move == 'L') {
                currX -= curr.length;
            } else if (curr.move == 'U') {
                currY -= curr.length;
            } else if (curr.move == 'D') {
                currY += curr.length;
            }

            left = std::min(currX, left);
            right = std::max(currX, right);
            top = std::min(currY, top);
            bottom = std::max(currY, bottom);
        }

        int x = top * -1;
        int y = left * -1;
        for (int i=0;i<inputs.size();i++) {
            input curr = inputs[i];

            if (curr.move == 'R') {
                for (int k=0;k<curr.length;k++) {
                    y++;
                    world[x][y] = '#';
                }
            } else if (curr.move == 'L') {
                for (int k=0;k<curr.length;k++) {
                    y--;
                    world[x][y] = '#';
                }
            } else if (curr.move == 'U') {
                for (int k=0;k<curr.length;k++) {
                    x--;
                    world[x][y] = '#';
                }
            } else if (curr.move == 'D') {
                for (int k=0;k<curr.length;k++) {
                    x++;
                    world[x][y] = '#';
                }
            }
        }

        for (int i = 0; i < world.size();i++) {
            for (int j = 0; j < world[0].size();j++) {
                if (world[i][j] == '#') {
                    total++;
                }
            }
        }

        for (int j = 0; j< world[0].size();j++) {
            floodFill(0, j);
            floodFill(n-1,j);
        }

        for (int i = 0; i< world.size();i++) {
            floodFill(i, 0);
            floodFill(i,m-1);
        }

        for (int i = 0; i < world.size();i++) {
            for (int j = 0; j < world[0].size();j++) {
                if (world[i][j] == '.') {
                    total++;
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

// 48414 too high