//
// Created by Maksym Kostynskyi on 03.12.2023.
//

#include "day_three.h"
#include <string>
#include <vector>
#include <cctype>
#include <set>
using namespace  std;

bool is_symbol(char c)
{
    return !isdigit(c) && c != '.';
}

// Part One
int sum_part_numbers_one(const vector<string>& input)
{
    set<pair<int, int>> digit_indices;
    int sum = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].length(); j++) {
            if (!is_symbol(input[i][j])) {
                continue;
            }
            bool is_last_row = i >= input.size()-1;
            bool is_last_element = j >= input[i].size()-1;
            bool is_first_row = i == 0;
            bool is_first_element = j == 0;
            if (!is_last_row) {
                if (isdigit(input[i+1][j])) {
                    digit_indices.insert(make_pair(i+1, j));
                }
                if (!is_last_element) {
                    if (isdigit(input[i+1][j+1])) {
                        digit_indices.insert(make_pair(i+1, j+1));
                    }
                }
            }

            if (!is_last_element) {
                if (isdigit(input[i][j+1])) {
                    digit_indices.insert(make_pair(i, j+1));
                }
            }

            if (!is_first_row) {
                if (isdigit(input[i-1][j])) {
                    digit_indices.insert(make_pair(i-1, j));
                }
                if (!is_first_element) {
                    if (isdigit(input[i-1][j-1])) {
                        digit_indices.insert(make_pair(i-1, j-1));
                    }
                }
            }

            if (!is_first_element) {
                if (isdigit(input[i][j-1])) {
                    digit_indices.insert(make_pair(i, j-1));
                }
            }

            if (!is_last_row && !is_first_element) {
                if (isdigit(input[i+1][j-1])) {
                    digit_indices.insert(make_pair(i+1, j-1));
                }
            }

            if (!is_first_row && !is_last_element) {
                if (isdigit(input[i-1][j+1])) {
                    digit_indices.insert(make_pair(i-1, j+1));
                }
            }

        }
    }

    set<pair<int, int>> passed_indices;
    vector<string> digits_str;
    string temp_str;
    for (const auto& p: digit_indices) {
        if (passed_indices.find(p) != passed_indices.end()) {
            continue;
        }
        temp_str = "";
        for (int i = p.first, j = p.second, k = p.second + 1; isdigit(input[i][j]) || isdigit(input[i][k]);) {
            if (isdigit(input[i][j])) {
                temp_str = string(1, input[i][j]).append(temp_str);
                passed_indices.insert(make_pair(i, j));
                j--;
            }

            if (isdigit(input[i][k])) {
                temp_str = temp_str.append(string(1, input[i][k]));
                passed_indices.insert(make_pair(i, k));
                k++;
            }
        }
        digits_str.push_back(temp_str);
    }
    for (const auto& s: digits_str) {
        sum += stoi(s);
    }

    return sum;
}

// Part Two
long sum_part_numbers(const vector<string>& input)
{
    set<pair<int, int>> digit_indices;
    long sum = 0;
    set<pair<int, int>> passed_indices;
    vector<string> digits_str;
    string temp_str;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].length(); j++) {
            if (input[i][j] != '*') {
                continue;
            }
            digit_indices.clear();
            bool is_last_row = i >= input.size()-1;
            bool is_last_element = j >= input[i].size()-1;
            bool is_first_row = i == 0;
            bool is_first_element = j == 0;
            if (!is_last_row) {
                if (isdigit(input[i+1][j])) {
                    digit_indices.insert(make_pair(i+1, j));
                }
                if (!is_last_element) {
                    if (isdigit(input[i+1][j+1])) {
                        digit_indices.insert(make_pair(i+1, j+1));
                    }
                }
            }

            if (!is_last_element) {
                if (isdigit(input[i][j+1])) {
                    digit_indices.insert(make_pair(i, j+1));
                }
            }

            if (!is_first_row) {
                if (isdigit(input[i-1][j])) {
                    digit_indices.insert(make_pair(i-1, j));
                }
                if (!is_first_element) {
                    if (isdigit(input[i-1][j-1])) {
                        digit_indices.insert(make_pair(i-1, j-1));
                    }
                }
            }

            if (!is_first_element) {
                if (isdigit(input[i][j-1])) {
                    digit_indices.insert(make_pair(i, j-1));
                }
            }

            if (!is_last_row && !is_first_element) {
                if (isdigit(input[i+1][j-1])) {
                    digit_indices.insert(make_pair(i+1, j-1));
                }
            }

            if (!is_first_row && !is_last_element) {
                if (isdigit(input[i-1][j+1])) {
                    digit_indices.insert(make_pair(i-1, j+1));
                }
            }
            passed_indices.clear();
            digits_str.clear();
            for (const auto& p: digit_indices) {
                if (passed_indices.find(p) != passed_indices.end()) {
                    continue;
                }
                temp_str = "";
                for (int row = p.first, b = p.second, k = p.second + 1; isdigit(input[row][b]) || isdigit(input[row][k]);) {
                    if (isdigit(input[row][b])) {
                        temp_str = string(1, input[row][b]).append(temp_str);
                        passed_indices.insert(make_pair(row, b));
                        b--;
                    }

                    if (isdigit(input[row][k])) {
                        temp_str = temp_str.append(string(1, input[row][k]));
                        passed_indices.insert(make_pair(row, k));
                        k++;
                    }
                }
                digits_str.push_back(temp_str);
            }

            if (digits_str.size() == 2) {
                sum += stoi(digits_str[0]) * stoi(digits_str[1]);
            }
        }
    }




    return sum;
}
