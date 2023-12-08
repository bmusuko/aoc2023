#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {
        std::string line;

        std::string red = "red";
        std::string green = "green";
        std::string blue = "blue";

        int total = 0;


        while (std::getline(file, line)) {
            int col_pos = line.find(':');
            std::string game_num_str = line.substr(5, col_pos);
            int game_number = std::atoi(game_num_str.c_str());

            std::string operation = line.substr(col_pos+1);

            std::string _action;
            std::istringstream ss(operation);
            std::vector<std::string> actions;
            while (std::getline(ss, _action, ';')) {
                actions.push_back(_action);
            }

            int curr_red = 0;
            int curr_green = 0;
            int curr_blue = 0;
            for (std::string action: actions) {
                std::string _show;
                std::istringstream sss(action);
                std::vector<std::string> shows;
                while(std::getline(sss, _show, ',')) {
                    shows.push_back(_show);
                }

                for (std::string show: shows) {
                    show = show.substr(1);
                    int space_pos = show.find(' ');

                    int count = std::atoi(show.substr(0, space_pos).c_str());
                    std::string color = show.substr(space_pos+1);

                    if (color == red) {
                        curr_red = std::max(curr_red, count);
                    } else if (color == green) {
                        curr_green = std::max(curr_green, count);
                    } else if (color == blue) {
                        curr_blue = std::max(curr_blue, count);
                    }
                }
            }

            total += (curr_red * curr_green * curr_blue);
        }

        std::cout << total << std::endl;
        file.close();
    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}