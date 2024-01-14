//
// Created by benedict on 1/14/24.
//

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>

#define LOG(x) std::cout << x << std::endl;

// using namespace std;



inline int task4(const string& filename, bool verbose) {
    int total = 0;

    ifstream f(filename);
    string line;
    string winners;
    string numbers;
    int split;

    if (!f.is_open()) {
        LOG("Read error, please check path.");
        return total;
    }

    map<int, int> winningNums;

    while (getline(f, line)) {
        if (verbose)
            LOG(line);

        // clean text
        line = line.substr(line.find(":") + 2);

        // split winners and numbers
        split = line.find("|");
        winners = line.substr(0, split);
        numbers = line.substr(split + 2);

        while (winners.length() > 0) {
            string numStr = winners.substr(0, winners.find(" "));
            if (numStr != "") {
                int num = stoi(numStr);
                winningNums[num] = 1;
            }
            if (winners.length() > numStr.length() + 1)
                winners = winners.substr(numStr.length() + 1); // clip winners
            else {break;}

        }


        // now search numbers
        int count = 0;

        while (numbers.length() > 0) {
            string numStr = numbers.substr(0, numbers.find(" "));
            if (numStr != "") {
                int num = stoi(numStr);
                int value = winningNums[num];
                if (value ==  1) {
                    count++;
                }
            }

            if (numbers.length() > numStr.length()+1)
                numbers = numbers.substr(numStr.length()+1); // clip numbers
            else {break;}

        }
        int winnings = (int)pow(2.0, (double) count - 1);
        total += winnings;
        winningNums.clear();
        // break;
    }
    return total;
}