//
// Created by benedict on 1/13/24.
//

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#define log(x) std::cout << x << std::endl;

using namespace std;

inline void logMatrix(const vector<vector<int>>& mat, unsigned const int m, unsigned const int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
}

inline int checkAdjacency(
    const vector<vector<int>>& mat,
    unsigned const int m,
    unsigned const int n,
    unsigned const int xi,
    unsigned const int xj
) {
    bool leftEdge = true;
    bool rightEdge = true;

    // check left
    if (xj > 0) {
        leftEdge = false;
        if (mat[xi][xj-1] == -2)
            return true;
    }
    // check right
    if (xj < n - 1) {
        rightEdge = false;
        if (mat[xi][xj+1] == -2)
            return true;
    }

    // check row above
    if (xi > 0) {
        if (!leftEdge && mat[xi-1][xj-1] == -2) {return true;} // top left
        if (mat[xi-1][xj] == -2) {return true;} // above
        if (!rightEdge && mat[xi-1][xj+1] == -2) {return true;} // top right
    }

    // check row below
    if (xi < m - 1) {
        if (!leftEdge && mat[xi+1][xj-1] == -2) {return true;} // bottom left
        if (mat[xi+1][xj] == -2) {return true;} // below
        if (!rightEdge && mat[xi+1][xj+1] == -2) {return true;} // bottom right
    }

    return false;

}

inline void formatVectorCoords(vector<int> &coords, unsigned const int x, unsigned const int y) {
    coords[0] = x;
    coords[1] = y;
}

inline vector<int> findAdjLoc(
    const vector<vector<int>>& mat,
    unsigned const int m,
    unsigned const int n,
    unsigned const int xi,
    unsigned const int xj
) {
    bool leftEdge = true;
    bool rightEdge = true;
    vector<int> coords(2);
    coords[0] = -1;
    coords[1] = -1;

    // check left
    if (xj > 0) {
        leftEdge = false;
        if (mat[xi][xj-1] == -2) {formatVectorCoords(coords, xi, xj-1); return coords;}

    }
    // check right
    if (xj < n - 1) {
        rightEdge = false;
        if (mat[xi][xj+1] == -2) {formatVectorCoords(coords, xi, xj+1); return coords;}
    }

    // check row above
    if (xi > 0) {
        if (!leftEdge && mat[xi-1][xj-1] == -2) {formatVectorCoords(coords, xi-1, xj-1); return coords;} // top left
        if (mat[xi-1][xj] == -2) {formatVectorCoords(coords, xi-1, xj); return coords;} // above
        if (!rightEdge && mat[xi-1][xj+1] == -2) {formatVectorCoords(coords, xi-1, xj+1); return coords;} // top right
    }

    // check row below
    if (xi < m - 1) {
        if (!leftEdge && mat[xi+1][xj-1] == -2) {formatVectorCoords(coords, xi+1, xj-1); return coords;} // bottom left
        if (mat[xi+1][xj] == -2) {formatVectorCoords(coords, xi+1, xj); return coords;} // below
        if (!rightEdge && mat[xi+1][xj+1] == -2) {formatVectorCoords(coords, xi+1, xj+1); return coords;} // bottom right
    }

    return coords;

}


inline int task3part1(const string& filename, bool verbose) {
    int total = 0;

    ifstream f(filename);
    string line;

    if (!f.is_open()) {
        log("Read error, please check path.");
        return total;
    }

    int i = 0;

    // mxn rows x cols
    typedef vector<vector<int>> intMat;
    intMat mat;
    vector<int> row;

    // populate matrix
    while (getline(f, line)) {
        if (verbose)
            log(line);

        for (int j = 0; j < line.length(); j++) {
            char c = line[j];
            int x = static_cast<int>(line[j] - 48);
            int val;
            if (c == '.') {val = -1;}
            else if (x >= 0 && x < 10) {val = x;}
            else {val = -2;}
            row.push_back(val);
        }
        row.push_back(-1);
        mat.push_back(row);
        row.clear();
        i++;
    }

    // m rows x n cols, unsigned means there can only be positive values (signed meaning both positive and negative
    unsigned int m = mat.size();
    unsigned int n = mat[0].size();

    if (verbose) {
        log("Matrix:");
        logMatrix(mat, m, n);
    }

    // now traverse matrix looking for adjacent symbols (i.e. -1s)
    int currentElement;
    string number;
    int adjTotal;
    vector<int> adjNumbers;

    // simple matrix traversal
    for (int i = 0; i < m; i++) {
        number = "";
        adjTotal = 0;
        for (int j = 0; j < n; j++) {
            currentElement = mat[i][j];

            if (currentElement >= 0) {  // is a number
                number += to_string(currentElement);

                /*
                find if current number has any adjacent symbols if so,
                find the complete number and accumulate the value
                */

                adjTotal += checkAdjacency(mat, m, n , i, j);
                // log(number << " " << adjTotal);
            }
            else {  // reset number
                if (!number.empty() && adjTotal > 0) {
                    // log(number);
                    adjNumbers.push_back(stoi(number));
                }
                number = "";
                adjTotal = 0;
            }
        }
    }
    for (int i: adjNumbers) {
        // log(i);
        total += i;

    }
    return total;
}



// part 2
inline int task3(const string& filename, bool verbose) {

    // store adjacent star location with numbers (key, value of hashmap) as we traverse matrix, if a key already exists, we add the new number to a vector
    // finally, we loop through the hashmap and locaate hashmaps with values of length 2 and accumulate their product

    int total = 0;

    ifstream f(filename);
    string line;

    if (!f.is_open()) {
        log("Read error, please check path.");
        return total;
    }

    int i = 0;

    // mxn rows x cols
    typedef vector<vector<int>> intMat;
    intMat mat;
    vector<int> row;

    // populate matrix
    while (getline(f, line)) {
        if (verbose)
            log(line);

        for (int j = 0; j < line.length(); j++) {
            char c = line[j];
            int x = static_cast<int>(line[j] - 48);
            int val;
            if (c == '*') {val = -2;}
            else if (x >= 0 && x < 10) {val = x;}
            else {val = -1;}
            row.push_back(val);
        }
        row.push_back(-1);
        mat.push_back(row);
        row.clear();
        i++;
    }

    // m rows x n cols, unsigned means there can only be positive values (signed meaning both positive and negative
    unsigned int m = mat.size();
    unsigned int n = mat[0].size();

    map<string, vector<int>> adjMap;
    vector<int> adjLoc = {-1, -1};
    string number;
    int currentElement;

    // traverse matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            currentElement = mat[i][j];
            if (currentElement >= 0) {
                number += to_string(currentElement);
                if (number.empty() || (adjLoc[0] == -1 && adjLoc[1] == -1)) {
                    adjLoc = findAdjLoc(mat, m, n, i, j);
                }
            }
            else { // now the number is finished
                if (!number.empty() && (adjLoc[0] != -1 && adjLoc[1] != -1)) {
                    // log(number << " -> (" << adjLoc[0] << ", " << adjLoc[1] << ")");
                    string coords = "(" + to_string(adjLoc[0]) + ", " + to_string(adjLoc[1]) + ")";

                    // update hashmap
                    vector<int> numVec = adjMap[coords];
                    numVec.push_back(stoi(number));
                    adjMap[coords] = numVec;

                }
                number = "";
                adjLoc[0] = -1, adjLoc[1] = -1;
            }
        }
    }

    // traverse map to locate coords with two numbers and calculate their product

    for (auto& [coords, numVec]: adjMap) {
        // log("key: " << key << ", value: " << value[0] << ", " << value[1]);
        if (numVec.size() == 2) {
            total += numVec[0] * numVec[1];
        }

    }

    if (verbose) {
        log("Matrix:");
        logMatrix(mat, m, n);
    }
    return total;
}
