//
// Created by benedict on 1/13/24.
//

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <map>

#define LOG(x) std::cout << x << std::endl;

using namespace std;

inline int task2(const string& filename, bool verbose) {

    int total = 0;
    int power = 0;
    ifstream f(filename);
    string line;


    if ((bool)f == 0) {
        LOG("Stream error.");
        return 0;
    }

    map<string, int> mapping = {
        {"red", 12},
        {"green", 13},
        {"blue", 14}
    };

    map<string, int> colourMapping = {
        {"red", 0},
        {"green", 1},
        {"blue", 2}
    };

    int gameNumber = 1;
    while (getline(f, line)) {

        string round;
        int roundIdx;
        bool outcome = true;

        int maxRed = 0;
        int maxBlue= 0;
        int maxGreen = 0;

        do {
            roundIdx = line.find(";");
            round = line.substr(0, roundIdx);
            round = round.substr(round.find(":") + 2); // trim game substr

            string colour;
            int colourIdx = 0;
            int split;
            int num;
            string word;


            while (colourIdx != -1) {
                colourIdx = round.find(",");
                colour = round.substr(0, colourIdx);
                round = round.substr(colourIdx + 2);

                // split by white space now
                split = colour.find(" ");
                num = stoi(colour.substr(0, split));
                word = colour.substr(split + 1);

                if (num > mapping[word]) {
                    outcome = false;
                }

                // test for max values for each colour
                switch(colourMapping[word]) {
                    case 0:
                        if (num > maxRed) {maxRed = num;}
                        break;
                    case 1:
                        if (num > maxGreen) {maxGreen = num;}
                        break;
                    case 2:
                        if (num > maxBlue) {maxBlue = num;}
                        break;
                }
            }

            // update line
            line = line.substr(roundIdx + 1);

        } while (roundIdx != -1);

        if (outcome) {
            total += gameNumber;
        }

        gameNumber++;
        power += (maxRed * maxGreen * maxBlue);
        LOG("power = " << power)

    }





    return total;
}