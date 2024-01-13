//
// Created by Grey, Benedict P on 12/01/2024.
//

#include <iostream>
#include "day1/task1.h"

#define log(x) std::cout << x << std::endl;

int main(int argc, char* argv[]) {
    int code = task1("../day1/input.txt");
    log("Final code: " << code);
    return 0;
}
