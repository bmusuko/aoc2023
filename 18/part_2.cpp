#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct input {
    char move;
    int length;
    std::string color;
};

struct point {
    long long x;
    long long y;
};


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

            char dir;

            if (color[6] == '0') {
                dir = 'R';
            } else if (color[6] == '1') {
                dir = 'D';
            } else if (color[6] == '2') {
                dir = 'L';
            } else if (color[6] == '3') {
                dir = 'U';
            }

            int num = 0;
            for (int i = 1; i<=5;i++) {
                char c = color[i];
                int tt = 0;
                if (c == 'a') {
                    tt = 10;
                } else if (c == 'b') {
                    tt = 11;
                } else if (c == 'c') {
                    tt = 12;
                } else if (c == 'd') {
                    tt = 13;
                } else if (c == 'e') {
                    tt = 14;
                } else if (c == 'f') {
                    tt = 15;
                } else {
                    tt = c - '0';
                }

                num = (num * 16) + tt;
            }

            inputs.push_back({dir, num, color});
        }
        std::vector<point> points;
        points.push_back({0,0});

        long long currX, currY;
        long long temp;

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
            temp += curr.length;

            points.push_back({currX,currY});
        }



        for (int i = 0; i< points.size()-1; i++) {
            point currP = points[i];
            point nextP = points[i+1];
            total += (currP.x * nextP.y) - (currP.y * nextP.x);
            std::cout<<"x: "<<currP.x<<", y: "<<currP.y<<"\n";
        }


        file.close();

        // shoe-lace
        // pick's theorem
        std::cout << total / 2 + (temp / 2) + 1<< std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}
