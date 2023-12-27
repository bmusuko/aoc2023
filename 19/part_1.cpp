#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

struct part {
    long long x;
    long long m;
    long long a;
    long long s;
};

struct condition {
    char symbol;
    long long value;
    char compare;
    std::string next;
};

struct conditions {
    std::vector<condition> rules;
};

std::unordered_map<std::string, conditions> rule_map;

bool isAccepted(std::string key, part engine) {
    conditions rules = rule_map[key];

    if (key == "A") {
        return true;
    } else if (key == "R") {
        return false;
    }


    for (int i=0;i<rules.rules.size(); i++) {
        condition rule = rules.rules[i];

        if (rule.symbol == 0) {
            return isAccepted(rule.next, engine);
        }

        long long value = 0;

        if (rule.symbol == 'x') {
            value = engine.x;
        } else if (rule.symbol == 'm') {
            value = engine.m;
        } else if (rule.symbol == 'a') {
            value = engine.a;
        } else if (rule.symbol == 's') {
            value = engine.s;
        }

        if (rule.compare == '>') {
            if (value > rule.value) {
                return isAccepted(rule.next, engine);
            }
        } else if (rule.compare == '<') {
            if (value < rule.value) {
                return isAccepted(rule.next, engine);
            }
        }
    }
    return false;
}

int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        std::string line;
        std::vector<part> engines;


        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            if (line[0] == '{') {
                std::istringstream ss(line.substr(1, line.length()-2));
                std::string _num;

                part engine = {0,0,0,0};

                while (std::getline(ss, _num, ',')) {
                    int equal_pos = _num.find('=');
                    long long val = std::stoll(_num.substr(equal_pos+1, _num.size()-2));


                    if (_num[0] == 'x') {
                        engine.x = val;
                    } else if (_num[0] == 'm') {
                        engine.m = val;
                    } else if (_num[0] == 'a') {
                        engine.a = val;
                    } else if (_num[0] == 's') {
                        engine.s = val;
                    }
                }
                engines.push_back(engine);
            } else {
                int guard_pos = line.find('{');
                std::string rule_key = line.substr(0, guard_pos);
                std::istringstream ss(line.substr(guard_pos+1, line.length()-(guard_pos+2)));

                conditions _condition;
                std::string _rule;

                while (std::getline(ss, _rule, ',')) {
                    int equal_pos = _rule.find(':');
                    condition _cond = {};

                    if (equal_pos == -1) {
                        _cond.next = _rule;
                    } else {
                        _cond.symbol = _rule[0];
                        _cond.compare = _rule[1];
                        _cond.value = std::stoll(_rule.substr(2, equal_pos-2));
                        _cond.next = _rule.substr(equal_pos+1,_rule.size()-(equal_pos+1));
                    }
                    _condition.rules.push_back(_cond);
                }
                rule_map[rule_key] = _condition;
            }

        }

        for (int i=0;i<engines.size();i++) {
            part engine = engines[i];

//            std::cout<<"x: "<<engine.x<<", m: "<<engine.m<<", a: "<<engine.a<<", s: "<<engine.s<<"\n";
            if (isAccepted("in", engine)) {
                total += engine.x + engine.m + engine.a + engine.s;
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
