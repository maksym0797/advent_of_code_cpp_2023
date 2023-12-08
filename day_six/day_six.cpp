//
// Created by Maksym Kostynskyi on 07.12.2023.
//

#include "day_six.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "../day_one/day_one.hpp"
using namespace std;
// part one
int multiply_ways_win_one(const vector<string>& inputs)
{
    istringstream time_iss(inputs[0]);
    time_iss.ignore(11);
    istringstream distance_iss(inputs[1]);
    distance_iss.ignore(11);
    int time, distance;
    int time_temp, distance_temp;
    int result = 1;
    int ways = 0;
    while (time_iss >> time && distance_iss >> distance) {;
        ways = 0;
        for(int speed = 1; speed < time; speed++) {
            time_temp = time - speed;
            if (speed * time_temp > distance) {
                ways++;
            }
        }
        result *= ways;
    }
    return result;
}

// part two
long multiply_ways_win(const vector<string>& inputs)
{
    istringstream time_iss(replaceAll(inputs[0], " ", ""));
    time_iss.ignore(5);
    istringstream distance_iss(replaceAll(inputs[1], " ", ""));
    distance_iss.ignore(9);
    long time, distance;
    long time_temp, distance_temp;
    long result = 1;
    long ways = 0;
    while (time_iss >> time && distance_iss >> distance) {;
        ways = 0;
        for(long speed = 1; speed < time; speed++) {
            time_temp = time - speed;
            if (speed * time_temp > distance) {
                ways++;
            }
        }
        result *= ways;
    }
    return result;
}