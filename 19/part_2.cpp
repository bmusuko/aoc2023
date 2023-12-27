#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

// inclusive range
struct range {
    long long start;
    long long end;
};

struct part {
    range x;
    range m;
    range a;
    range s;
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


long long countCombination(part engine) {
    return (engine.x.end - engine.x.start + 1) *
    (engine.m.end - engine.m.start + 1) *
    (engine.a.end - engine.a.start + 1) *
    (engine.s.end - engine.s.start + 1);
}

bool isValidRange(part engine) {
    return countCombination(engine) > 0;
}

long long numAccepted(std::string key, part engine) {
    if (!isValidRange(engine)) {
        return 0;
    }


    if (key == "A") {
        return countCombination(engine);
    } else if (key == "R") {
        return 0;
    }

    long long total = 0;
    part currEngine = engine;

    conditions rules = rule_map[key];
    for (int i=0;i<rules.rules.size(); i++) {
        condition rule = rules.rules[i];

        if (rule.symbol == 0) {
            total += numAccepted(rule.next, currEngine);
            break;
        }

        if (rule.compare == '>') {
            part nextEngine = currEngine;
            if (rule.symbol == 'x') {
                nextEngine.x.start = std::max(nextEngine.x.start+1, rule.value+1);
                currEngine.x.end = std::min(currEngine.x.end, rule.value);
            } else if (rule.symbol == 'm') {
                nextEngine.m.start = std::max(nextEngine.m.start+1, rule.value+1);
                currEngine.m.end = std::min(currEngine.m.end, rule.value);
            } else if (rule.symbol == 'a') {
                nextEngine.a.start = std::max(nextEngine.a.start+1, rule.value+1);
                currEngine.a.end = std::min(currEngine.a.end, rule.value);
            } else if (rule.symbol == 's') {
                nextEngine.s.start = std::max(nextEngine.s.start+1, rule.value+1);
                currEngine.s.end = std::min(currEngine.s.end, rule.value);
            }
            total += numAccepted(rule.next, nextEngine);
        } else if (rule.compare == '<') {
            part nextEngine = currEngine;
            if (rule.symbol == 'x') {
                nextEngine.x.end = std::min(nextEngine.x.end-1, rule.value-1);
                currEngine.x.start = std::max(currEngine.x.start, rule.value);
            } else if (rule.symbol == 'm') {
                nextEngine.m.end = std::min(nextEngine.m.end-1, rule.value-1);
                currEngine.m.start = std::max(currEngine.m.start, rule.value);
            } else if (rule.symbol == 'a') {
                nextEngine.a.end = std::min(nextEngine.a.end-1, rule.value-1);
                currEngine.a.start = std::max(currEngine.a.start, rule.value);
            } else if (rule.symbol == 's') {
                nextEngine.s.end = std::min(nextEngine.s.end-1, rule.value-1);
                currEngine.s.start = std::max(currEngine.s.start, rule.value);
            }
            total += numAccepted(rule.next, nextEngine);
        }
    }

    return total;
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
                continue;
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

        total = numAccepted("in", {{1, 4000}, {1,4000}, {1,4000}, {1,4000}});

        file.close();
        std::cout << total << std::endl;
    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}