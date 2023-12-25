#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

enum DIRECTION {
    LEFT = 1,
    TOP = 2,
    RIGHT = 3,
    BOTTOM = 4,
};

struct Point {
    int x;
    int y;
    int d;
};

struct Node {
    Point point;
    DIRECTION direction;
    long long cost;
    int consecutive;
};


struct MinHeapComparator {
    bool operator()(const Node& a, const Node& b) {
        return a.cost > b.cost;  // This makes it a min-heap
    }
};

std::string getKey(int x, int y, int consecutive, DIRECTION d) {
    return std::to_string(x) + "#" + std::to_string(y) + "#" + std::to_string(consecutive) + "#" + std::to_string(d);
}


int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        std::string line;
        std::vector<std::vector<int> > world; // extended row



        while (std::getline(file, line)) {
            std::vector<int> row;
            for (int i = 0; i<line.size();i++) {
                row.push_back(line[i]-'0');
            }
            world.push_back(row);
        }

        int n = world.size();
        int m = world[0].size();

        std::priority_queue<Node, std::vector<Node>, MinHeapComparator> minHeap;


        std::unordered_map<std::string, bool> visited;
        Point initPoint = {0,0};
        visited[getKey(0,0, -1, RIGHT)] = true;
        minHeap.push({initPoint,RIGHT,0,-1});

        while (!minHeap.empty()) {
            Node node = minHeap.top();
            minHeap.pop();
//            std::cout <<"(" << node.point.x <<"," << node.point.y <<"," <<node.cost <<"," <<node.consecutive<< ")\n";



            if (node.point.x == n-1 && node.point.y == m-1) {
                std::cout << "cost: "<< node.cost << std::endl;
                return 0;
            }

            // turn left
            int dx1 = 0;
            int dy1 = 0;
            DIRECTION d1;

            if (node.direction == RIGHT) {
                dx1 = -1;
                d1 = TOP;
            } else if (node.direction == TOP) {
                dy1 = -1;
                d1 = LEFT;
            } else if (node.direction == LEFT) {
                dx1 = 1;
                d1 = BOTTOM;
            } else if (node.direction == BOTTOM) {
                dy1 = 1;
                d1 = RIGHT;
            }
            int leftX = node.point.x + dx1;
            int leftY = node.point.y + dy1;

            if (leftX >= 0 && leftX < n && leftY >= 0 && leftY < m && !visited[getKey(leftX, leftY, 0,d1)]) {
                visited[getKey(leftX, leftY, 0, d1)] = true;
                Point leftPoint = {leftX, leftY, d1};
                minHeap.push({leftPoint, d1, node.cost + world[leftX][leftY],0});
            }



            // turn right
            int dx2 = 0;
            int dy2 = 0;
            DIRECTION d2;

            if (node.direction == RIGHT) {
                dx2 = 1;
                d2 = BOTTOM;
            } else if (node.direction == TOP) {
                dy2 = 1;
                d2 = RIGHT;
            } else if (node.direction == LEFT) {
                dx2 = -1;
                d2 = TOP;
            } else if (node.direction == BOTTOM) {
                dy2 = -1;
                d2 = LEFT;
            }
            int rightX = node.point.x + dx2;
            int rightY = node.point.y + dy2;

            if (rightX >= 0 && rightX < n && rightY >= 0 && rightY < m && !visited[getKey(rightX, rightY, 0,d2)]) {
                visited[getKey(rightX, rightY, 0,d2)] = true;
                Point rightPoint = {rightX, rightY, d2};
                minHeap.push({rightPoint, d2, node.cost + world[rightX][rightY],0});
            }

            // continue
            if (node.consecutive < 2) {
                int dx3 = 0;
                int dy3 = 0;
                if (node.direction == LEFT) {
                    dy3 = -1;
                } else if (node.direction == RIGHT) {
                    dy3 = 1;
                } else if (node.direction == TOP) {
                    dx3 = -1;
                } else if (node.direction == BOTTOM) {
                    dx3 = 1;
                }

                int cX = node.point.x + dx3;
                int cY = node.point.y + dy3;


                if (cX >= 0 && cX < n && cY >= 0 && cY < m && !visited[getKey(cX, cY, node.consecutive + 1,node.direction)]) {
                    visited[getKey(cX, cY, node.consecutive + 1,node.direction)] = true;
                    Point cPoint = {cX, cY, node.direction};
                    minHeap.push({cPoint, node.direction, node.cost + world[cX][cY], node.consecutive + 1});
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