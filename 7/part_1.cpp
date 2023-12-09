#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <cmath>
#include <unordered_map>

struct camel {
    std::string card;
    int bid;
};

void printVector(const std::vector<camel>& vec) {
    std::cout << "Vector elements: \n";
    for (const auto& element : vec) {
        std::cout << element.card << " ";
        std::cout << element.bid << " " << std::endl;

    }
    std::cout << std::endl;
}

int point(std::string card) {
    std::unordered_map<char, int> charMap;
    for (char c: card) {
        charMap[c]++;
    }

    int pairCount = 0;
    int threeCount = 0;
    for (const auto& pair : charMap) {
        if (pair.second == 5) {
            return 7;
        }
        // four a kind 6
        if (pair.second == 4) {
            return 6;
        }

        if (pair.second == 2 && pair.first != 'J') {
            pairCount++;
        }
        if (pair.second == 3 && pair.first != 'J') {
            threeCount++;
        }
    }

    // full house 5
    if (pairCount == 1 && threeCount == 1) {
        return 5;
    }
    // 3 of a kind 4
    if (threeCount == 1) {
        return 4;
    }
    // two pair 3
    if (pairCount == 2) {
        return 3;
    }
    // one pair 2
    if (pairCount == 1) {
        return 2;
    }
    // high card 1
    return 1;
}

bool compare(camel left, camel right) {
    int pointLeft = point(left.card);
    int pointRight = point(right.card);
    if (pointLeft != pointRight) {
        return pointLeft > pointRight;
    }

    std::unordered_map<char, int> cardMap;
    cardMap['A'] = 14;
    cardMap['K'] = 13;
    cardMap['Q'] = 12;
    cardMap['J'] = 11;
    cardMap['T'] = 10;
    cardMap['9'] = 9;
    cardMap['8'] = 8;
    cardMap['7'] = 7;
    cardMap['6'] = 6;
    cardMap['5'] = 5;
    cardMap['4'] = 4;
    cardMap['3'] = 3;
    cardMap['2'] = 2;


    for (int i = 0; i< left.card.size(); i++) {
        int leftValue = cardMap[left.card[i]];
        int rightValue = cardMap[right.card[i]];

        if (leftValue != rightValue) {
            return leftValue > rightValue;
        }
    }
    return true;
}

void merge(std::vector<camel>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays to hold the two halves
    std::vector<camel> leftArray(n1);
    std::vector<camel> rightArray(n2);

    // Copy data to temporary arrays leftArray[] and rightArray[]
    for (int i = 0; i < n1; i++)
        leftArray[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (compare(leftArray[i], rightArray[j])) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArray[], if there are any
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArray[], if there are any
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<camel>& arr, int left, int right) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}





int main() {
    std::ifstream file("input.txt");

    if (file.is_open()) {

        long long total = 0;
        std::vector<camel> camels;
        std::string line;


        while (std::getline(file, line)) {
            int space_col = line.find(' ');
            camel curCamel = {
                    line.substr(0, space_col),
                    std::atoi(line.substr(space_col+1).c_str()),
            };
            camels.push_back(curCamel);
        }
        file.close();


        mergeSort(camels, 0, camels.size());


        int multiplier = camels.size();
        for (int i = 0; i< camels.size(); i++) {
            total += camels[i].bid * multiplier;
            multiplier--;
        }
        printVector(camels);

        std::cout << total << std::endl;

    } else {
        std::cout << "Failed to open file";
        return -1;
    }

    return 0;
}