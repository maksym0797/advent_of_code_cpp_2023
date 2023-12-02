//
//  day_one.cpp
//  advent_of_code_2023_cpp
//
//  Created by Maksym Kostynskyi on 01.12.2023.
//

#include "day_one.hpp"
#include <string>
#include <regex>
#include <vector>
using namespace  std;

string replaceAll(std::string str, const std::string& from, const std::string& to) {
    if (from.empty()) {
        return str;
    }
    size_t startPos = 0;
    while ((startPos = str.find(from, startPos)) != std::string::npos) {
        str.replace(startPos, from.length(), to);
        startPos += to.length(); // Handles cases where 'to' is a substring of 'from'
    }
    return str;
}

int sum_all_calibration_values(const vector<string>& input)
{
    int sum = 0;
    string only_numbers;
    string temp;
    regex non_number_regex("[^0-9]");
    for (const string& str: input) {
        temp = str;
        temp = replaceAll(temp, "one", "one1one");
        temp = replaceAll(temp, "two", "two2two");
        temp = replaceAll(temp, "three", "three3three");
        temp = replaceAll(temp, "four", "four4four");
        temp = replaceAll(temp, "five", "five5five");
        temp = replaceAll(temp, "six", "six6six");
        temp = replaceAll(temp, "seven", "seven7seven");
        temp = replaceAll(temp, "eight", "eight8eight");
        temp = replaceAll(temp, "nine", "nine9nine");
        
        only_numbers = regex_replace(temp, non_number_regex, "");
        sum += (only_numbers[0] - '0') * 10 + (only_numbers[only_numbers.length()-1] - '0');
    }
    return sum;
}
