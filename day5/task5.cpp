//
// Created by benedict on 1/21/24.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "task5.h"

#define LOG(x) std::cout << x << std::endl;

using namespace std;

struct Map {
    long long start;
    long long length;
    long long transformation;
};

struct SeedRange {
    long long start;
    long long end;
};


// declare maps
vector<Map> seed_to_soil_map;
vector<Map> soil_to_fertilizer_map;
vector<Map> fertilizer_to_water_map;
vector<Map> water_to_light_map;
vector<Map> light_to_temperature_map;
vector<Map> temperature_to_humidity_map;
vector<Map> humidity_to_location_map;


void printMap(vector<Map>& map) {
    for (Map m: map) {
        LOG(m.start << ", " << m.length << ", " << m.transformation);
    }
}

vector<long long> extractNums(string subStr) {
    vector<long long> nums;
    long long num;
    int splitIdx;
    // takes a string containing numbers and coverts into a vector of ints
    while (subStr.length() > 0) {
        splitIdx = subStr.find(" ");
        // LOG(subStr.substr(0, splitIdx) << ", " << subStr);
        num = stoll(subStr.substr(0, splitIdx));

        nums.push_back(num);
        subStr = subStr.substr(splitIdx+1);
        if (splitIdx == -1)
            break;
    }
    return nums;
}


vector<SeedRange> buildSeedRanges(vector<long long> &seeds) {
    vector<SeedRange> seedRanges;
    for (int i = 0; i < seeds.size() - 1; i+=2) {
        long long start = seeds[i];
        long long end = seeds[i] + seeds[i+1];
        seedRanges.push_back({start, end});
    }
    return seedRanges;
}


void forwardMap(long long &seed) {
    for (Map map: seed_to_soil_map) {
        if (seed >= map.start && seed <= map.start + map.length) {
            seed += map.transformation;
            break;
        }
    }
    for (Map map: soil_to_fertilizer_map) {
        if (seed >= map.start && seed <= map.start + map.length) {
            seed += map.transformation;
            break;
        }
    }
    for (Map map: fertilizer_to_water_map) {
        if (seed >= map.start && seed <= map.start + map.length) {
            seed += map.transformation;
            break;
        }
    }
    for (Map map: water_to_light_map) {
        if (seed >= map.start && seed <= map.start + map.length) {
            seed += map.transformation;
            break;
        }
    }
    for (Map map: light_to_temperature_map) {
        if (seed >= map.start && seed <= map.start + map.length) {
            seed += map.transformation;
            break;
        }
    }
    for (Map map: temperature_to_humidity_map) {
        if (seed >= map.start && seed <= map.start + map.length) {
            seed += map.transformation;
            break;
        }
    }
    for (Map map: humidity_to_location_map) {
        if (seed >= map.start && seed <= map.start + map.length) {
            seed += map.transformation;
            break;
        }
    }
}

long inverseMap(long long &loc) {
    for (Map map: humidity_to_location_map) {
        if (loc >= (map.start + map.transformation) && loc <= (map.start + map.length + map.transformation)) {
            loc -= map.transformation;
            break;
        }
    }
    for (Map map: temperature_to_humidity_map) {
        if (loc >= (map.start + map.transformation) && loc <= (map.start + map.length + map.transformation)) {
            loc -= map.transformation;
            break;
        }

    }
    for (Map map: light_to_temperature_map) {
        if (loc >= (map.start + map.transformation) && loc <= (map.start + map.length + map.transformation)) {
            loc -= map.transformation;
            break;
        }
    }
    for (Map map: water_to_light_map) {
        if (loc >= (map.start + map.transformation) && loc <= (map.start + map.length + map.transformation)) {
            loc -= map.transformation;
            break;
        }
    }
    for (Map map: fertilizer_to_water_map) {
        if (loc >= (map.start + map.transformation) && loc <= (map.start + map.length + map.transformation)) {
            loc -= map.transformation;
            break;
        }
    }
    for (Map map: soil_to_fertilizer_map) {
        if (loc >= (map.start + map.transformation) && loc <= (map.start + map.length + map.transformation)) {
            loc -= map.transformation;
            break;
        }
    }
    for (Map map: seed_to_soil_map) {
        if (loc >= (map.start + map.transformation) && loc <= (map.start + map.length + map.transformation)) {
            loc -= map.transformation;
            break;
        }
    }
    return loc;
}


long long task5(const string& filename, bool verbose) {
    ifstream f(filename);
    string line;
    int counter = -1;

    if (!f.is_open()) {
        LOG("Read error, please check path.");
        return -1;
    }

    // get first line for seeds
    getline(f, line);
    vector<long long> seeds = extractNums(line.substr(7));
    vector<SeedRange> seedRanges = buildSeedRanges(seeds);

    bool isNum = false;
    while (getline(f, line)) {
        if (line.length() < 2) {
            continue;
        }
        int delim = line.find("map:");
        if (delim != -1) { // found new batch of numbers
            isNum = true;
            counter++;
        }
        else if (isNum) {
            // process row of numbers, i.e. one map
            string numbers = line;
            vector<long long> nums = extractNums(numbers);
            switch(counter) {
                case 0:
                    seed_to_soil_map.push_back({nums[1], nums[2], nums[0]-nums[1]});
                    break;
                case 1:
                    soil_to_fertilizer_map.push_back({nums[1], nums[2], nums[0]-nums[1]});
                    break;
                case 2:
                    fertilizer_to_water_map.push_back({nums[1], nums[2], nums[0]-nums[1]});
                    break;
                case 3:
                    water_to_light_map.push_back({nums[1], nums[2], nums[0]-nums[1]});
                    break;
                case 4:
                    light_to_temperature_map.push_back({nums[1], nums[2], nums[0]-nums[1]});
                    break;
                case 5:
                    temperature_to_humidity_map.push_back({nums[1], nums[2], nums[0]-nums[1]});
                    break;
                case 6:
                    humidity_to_location_map.push_back({nums[1], nums[2], nums[0]-nums[1]});
                    break;
                default:
                    throw invalid_argument("Gone too far during data parsing!");
            }

        }

    }


    for (long long i = 0; i < 1e10; i++) {
        long long seed = inverseMap(i);

        // check to see if the inversed seed is in any of the ranges
        for (SeedRange sr: seedRanges) {
            if (seed >= sr.start && seed < sr.end - 1) {
                LOG("SEED = " << seed << ": " << sr.start << ", " << sr.end << ", therefore lowest location = " << i);
                return i;
            }
        }
    }
    // works but slow
    long minSeed = INT64_MAX;


    return minSeed;

}