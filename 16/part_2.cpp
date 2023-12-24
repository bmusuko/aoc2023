#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

enum DIRECTION {
    LEFT = 1,
    TOP = 2,
    RIGHT = 3,
    BOTTOM = 4,
};

struct point {
    long long x;
    long long y;
    DIRECTION d;
};

void printMatrix(const std::vector<std::vector<char> >& matrix) {
    for (const auto& row : matrix) {
        for (const char& ch : row) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::string getKey(point p) {
    return std::to_string(p.x) + "#" + std::to_string(p.y);
}

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        std::string line;
        std::vector<std::vector<char> > world; // extended row
        std::vector<std::vector<char> > world2; // extended row



        while (std::getline(file, line)) {
            std::vector<char> row;
            std::vector<char> row2;
            for (int i = 0; i<line.size();i++) {
                row.push_back(line[i]);
                row2.push_back(line[i]);
            }
            world.push_back(row);
            world2.push_back(row2);
        }

        int n = world.size();
        int m = world[0].size();

        std::cout<<"n: "<<n<<", m: "<<m<<"\n";

        std::vector<point> starts;

        for (int i=0;i<n;i++) {
            starts.push_back({i,0,RIGHT});
            starts.push_back({i,m-1,LEFT});
        }
        for (int j=0;j<m;j++) {
            starts.push_back({0,j,BOTTOM});
            starts.push_back({n-1,j,TOP});
        }


        for (int s=0;s<starts.size();s++) {
            std::vector<point> queue;
            std::unordered_map<std::string, bool> visited;

            queue.push_back(starts[s]);
            while (queue.size() >0 ) {
                std::vector<point> newQueue;

                for (int i=0;i<queue.size(); i++) {
                    point currPoint = queue[i];
//                std::cout<<"x: "<<currPoint.x<<", y: "<<currPoint.y<<", dir: "<<currPoint.d<<"\n";
                    if (currPoint.x < 0 || currPoint.x >= n || currPoint.y < 0 || currPoint.y >= m) {
//                    std::cout<<"[skipped] x: "<<currPoint.x<<", y: "<<currPoint.y<<", dir: "<<currPoint.d<<"\n";
                        continue;
                    }
//                std::cout<<"world: "<<world[currPoint.x][currPoint.y]<<std::endl;
                    world2[currPoint.x][currPoint.y] = '#';
//                printMatrix(world2);

                    std::string key = getKey(currPoint);
                    if (world[currPoint.x][currPoint.y] == '.') {
                        int dx = 0;
                        int dy = 0;
                        if (currPoint.d == LEFT) {
                            dy = -1;
                        } else if (currPoint.d == RIGHT) {
                            dy = 1;
                        } else if (currPoint.d == TOP) {
                            dx = -1;
                        } else if (currPoint.d == BOTTOM) {
                            dx = 1;
                        }

                        newQueue.push_back({currPoint.x + dx, currPoint.y + dy, currPoint.d});
                        visited[key] = true;
                    } else {
                        if (world[currPoint.x][currPoint.y] == '|' && !visited[key]) {
                            newQueue.push_back({currPoint.x-1, currPoint.y, TOP});
                            newQueue.push_back({currPoint.x+1, currPoint.y, BOTTOM});
                        } else if (world[currPoint.x][currPoint.y] == '-' && !visited[key]) {
                            newQueue.push_back({currPoint.x, currPoint.y-1, LEFT});
                            newQueue.push_back({currPoint.x, currPoint.y+1, RIGHT});
                        } else if (world[currPoint.x][currPoint.y] == '/') {
                            int dx = 0;
                            int dy = 0;
                            DIRECTION d = RIGHT;

                            if (currPoint.d == RIGHT) {
                                dx = -1;
                                d = TOP;
                            } else if (currPoint.d == TOP) {
                                dy = 1;
                                d = RIGHT;
                            } else if (currPoint.d == LEFT) {
                                dx = 1;
                                d = BOTTOM;
                            } else if (currPoint.d == BOTTOM){
                                dy = -1;
                                d = LEFT;
                            }
                            newQueue.push_back({currPoint.x + dx, currPoint.y + dy, d});
                        } else if (world[currPoint.x][currPoint.y] == '\\') {
                            int dx = 0;
                            int dy = 0;
                            DIRECTION d = RIGHT;

                            if (currPoint.d == RIGHT) {
                                dx = 1;
                                d = BOTTOM;
                            } else if (currPoint.d == TOP) {
                                dy = -1;
                                d = LEFT;
                            } else if (currPoint.d == LEFT) {
                                dx = -1;
                                d = TOP;
                            } else if (currPoint.d == BOTTOM){
                                dy = 1;
                                d = RIGHT;
                            }
                            newQueue.push_back({currPoint.x + dx, currPoint.y + dy, d});
                        }
                        visited[key] = true;
                    }
                }
                queue = newQueue;
            }
            long long currSize = visited.size();
            total = std::max(currSize, total);
        }

        file.close();

        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}