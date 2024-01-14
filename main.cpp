//
// Created by Grey, Benedict P on 12/01/2024.
//

#include <iostream>
#include <string>
#include "day1/task1.h"
#include "day2/task2.h"
#include "day3/task3.h"
#include "day4/task4.h"


#define LOG(x) std::cout << x << std::endl;


int main(int argc, char* argv[]) {
    // string s = "sevendxbninefour2fourclmln";
    // int idx = s.find_last_of("eight");
    // log(idx);

    int code = task4("../day4/input.txt", false);
    LOG("Final code: " << code);  // answer for test is 6756
    return 0;
}

