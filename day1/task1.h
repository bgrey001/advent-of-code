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

int task1(std::string filename) {

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
    int sum = 0;
    string line;

    if ((bool)f == 0) {
        log("Not working");
        return 0;
    }

    while (std::getline(f, line)) {
        int n = line.length();
        vector<string> vec;

        int min_idx = INT16_MAX;
        string min_str;

        int max_idx = 0;
        string max_str;

        // locate string ints
        for (const auto &[key, value]: mapping) {
            int idx1 = line.find_first_of(key);
            int idx2 = line.find_last_of(key);
            if (idx1 < min_idx && idx1 != -1) {
                min_idx = idx1;
                min_str = key;
            }
            if (idx2 > max_idx && idx2 != -1) {
                max_idx = idx2;
                max_str = key;
            }
        }

        log(line);

        log(min_str << " " << min_idx);
        log(max_str << " " << max_idx);


        if (!max_str.empty()) {
            line.replace(max_idx, max_str.length(), to_string(mapping[max_str]));
        }

        if (!min_str.empty()) {
            line.replace(min_idx, min_str.length(), to_string(mapping[min_str]));
        }
//        log(max_str);
//        log(line);

        for (int i = 0; i < n; i++) {
            int x = (int)line[i] - 48;
            if (x >= 0 && x < 10) {
                string s = to_string(x);
                vec.push_back(s);
            }
        }

        // locate strings
        int line_code;
        if (vec.size() == 0) {
            continue;
        }
        else {
            line_code = std::stoi(vec[0] + vec.back());
        }
        log(line_code);
        vec.clear();
        sum += line_code;
        break;
    }
    return sum;
}

