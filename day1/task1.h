//
// Created by Grey, Benedict P on 12/01/2024.
//

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <typeinfo>
#include <map>
#include <tuple>

#define log(x) std::cout << x << std::endl;

using namespace std;

// pass filename by reference to avoid making copies for each functionc call, this has to be constant as references can't be changed
inline int task1(const string& filename, bool verbose) {

    log(filename)

    map<std::string, int> mapping = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}
    };

    std::ifstream f(filename);
    std::ofstream fs;
    fs.open("../day1/output.txt");


    int sum = 0;
    string line;

    if ((bool)f == 0) {
        log("Not working");
        return 0;
    }

    int counter = 0;
    while (std::getline(f, line)) {

        if (verbose)
            log(line);

        int n = line.length();
        vector<string> vec;

        // word search
        int leftWordIdx = -1;
        string leftWord;

        int rightWordIdx = -1;
        string rightWord;

        for (int i = 0, j = n; j >= 0; i++, j--) {
            string leftSubstr = line.substr(0, i);
            string rightSubstr = line.substr(j, i);

            // loop through hashmap, refencing the pointer for each entry
            for (auto &[key, value]: mapping) {
                if (verbose)
                    log("key: " << key << ", value: " << value);

                // left string search
                if (leftWordIdx == -1) {
                    int leftIdx = leftSubstr.find(key);
                    if (leftIdx != -1) {
                        leftWordIdx = leftIdx;
                        leftWord = key;
                    }
                }

                // right string search
                if (rightWordIdx == -1) {
                    int rightIdx = rightSubstr.find(key);
                    if (rightIdx != -1) {
                        rightWordIdx = n - rightSubstr.length();
                        rightWord = key;
                    }
                }
            }
        }

        // replace words with integers now
        if (!rightWord.empty()) {
            line.replace(rightWordIdx, rightWord.length(), to_string(mapping[rightWord]));
        }

        if (!leftWord.empty() && leftWordIdx != rightWordIdx) {
            line.replace(leftWordIdx, leftWord.length(), to_string(mapping[leftWord]));
        }

        // integer search
        int left_int = -1;
        int right_int = -1;

        // dual pointer loop with extra condition to confirm both of our integers aren't set already
        for (int i = 0, j = n; j >= 0 && !(left_int != -1 && right_int != -1); i++, j--) {
            if (verbose)
                log("i: " << i << ", j: " << j);

            // forward pass to locate first integer
            int xi = (int)line[i] - 48;
            if (left_int == -1 && (xi >= 0 && xi < 10))
                left_int = xi;

            // backward pass to locate last integer
            int xj = (int)line[j] - 48;
            if (right_int == -1 && (xj >= 0 && xj < 10))
                right_int = xj;

        }

        int concat = std::stoi(to_string(left_int) + to_string(right_int));
        fs << concat << "\n";
        sum += concat;
        counter++;
    }
    fs.close();
    return sum;
}
