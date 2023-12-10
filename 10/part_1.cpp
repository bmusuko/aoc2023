#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

void printMatrix(const std::vector<std::vector<char> >& matrix) {
    for (const auto& row : matrix) {
        for (const char& ch : row) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }
}

struct point {
    int x;
    int y;
};

std::string getKey(point p) {
    return std::to_string(p.x) + "#" + std::to_string(p.y);
}

std::vector<point> next(char c, point currPoint) {
    int x = currPoint.x;
    int y = currPoint.y;

    std::vector<point> result;

    if (c == '|') {
        result.push_back({x-1, y});
        result.push_back({x+1, y});
    } else if (c == '-') {
        result.push_back({x, y-1});
        result.push_back({x, y+1});
    } else if (c == 'L') {
        result.push_back({x-1,y});
        result.push_back({x, y+1});
    } else if (c == 'J') {
        result.push_back({x-1, y});
        result.push_back({x, y-1});
    } else if (c == '7') {
        result.push_back({x+1, y});
        result.push_back({x, y-1});
    } else if (c == 'F') {
        result.push_back({x+1, y});
        result.push_back({x, y+1});
    } else if (c == 'S') {
        result.push_back({x+1,y});
        result.push_back({x-1,y});
        result.push_back({x,y+1});
        result.push_back({x,y-1});
    }

    return result;
}

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        std::string line;
        std::vector<std::vector<char> > world;
        point startingPoint;


        int i = 0;
        while (std::getline(file, line)) {
            std::vector<char> row;
            int j = 0;
            for (char c: line) {
                if (c == 'S') {
                    startingPoint = {i,j};
                }
                row.push_back(c);
                j++;
            }
            world.push_back(row);
            i++;
        }
        printMatrix(world);
        std::cout << "starting point: (" << startingPoint.x << "," << startingPoint.y << ")\n";
        int m = world.size();
        int n = world[0].size();
        // m x n


        std::vector<point> queue;
        std::unordered_map<std::string, bool> visited;
        queue.push_back(startingPoint);

        while (queue.size() > 0) {
            std::vector<point> nextQueue;
            for (int k = 0; k< queue.size(); k++) {
                point currPoint = queue[k];
                if (visited[getKey(currPoint)]) {
                    continue;
                }
                visited[getKey(currPoint)] = true;

                std::vector<point> nextPoints = next(world[currPoint.x][currPoint.y], currPoint);

                for (int l = 0; l < nextPoints.size(); l++) {
                    point futurePoint = nextPoints[l];

                    // not visited
                    if (visited[getKey(futurePoint)]) {
                        continue;
                    }

                    // valid coordinate
                    if (!(futurePoint.x >= 0 && futurePoint.x < m && futurePoint.y >= 0 && futurePoint.y < n)) {
                        continue;
                    }

                    if (world[futurePoint.x][futurePoint.y] == '.') {
                        continue;
                    }

                    std::vector<point> nextNextPoint = next(world[futurePoint.x][futurePoint.y], futurePoint);
                    bool isConnected = false;
                    for (int z = 0; z < nextNextPoint.size() && !isConnected; z++) {
                        point futureFuturePoints = nextNextPoint[z];

                        if (futureFuturePoints.x == currPoint.x && futureFuturePoints.y == currPoint.y) {
                            isConnected = true;
                            break;
                        }
                    }
                    if (!isConnected) {
                        continue;
                    }


                    nextQueue.push_back(futurePoint);
                }
            }
            queue.clear();
            queue = nextQueue;
            total++;
        }

        file.close();

        std::cout << total-1 << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}