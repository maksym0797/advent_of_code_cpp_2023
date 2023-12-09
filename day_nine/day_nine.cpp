//
// Created by Maksym Kostynskyi on 09.12.2023.
//

#include "day_nine.h"
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <iostream>
#include <numeric> // For std::gcd in C++17 and later
using namespace std;

// Part One
long sum_extrapolated_values(const vector<string>& inputs)
{
    vector<vector<long>> sequences;
    vector<long> temp_vec;
    long number;
    istringstream iss;
    for (const auto& input: inputs) {
        temp_vec.clear();
        iss.clear();
        iss.str(input);
        while (iss >> number) {
            temp_vec.push_back(number);
        }
        sequences.push_back(temp_vec);
    }
    long sum = 0;
    vector<vector<long>> sub_sequences;
    vector<vector<vector<long>>> history_sequences;
    sub_sequences.reserve(sequences.size());

    vector<long> temp_sequence;
    bool is_all_zero;
    for (const auto& sequence: sequences) {
        sub_sequences.clear();
        sub_sequences.push_back(sequence);
        temp_sequence = sequence;
        is_all_zero = false;
        while (!is_all_zero) {
            temp_vec.clear();
            for (int i = 0; i < temp_sequence.size() - 1; i++) {
                temp_vec.push_back(temp_sequence[i+1] - temp_sequence[i]);
            }
            sub_sequences.push_back(temp_vec);
            for (const auto& n: temp_vec) {
                is_all_zero = n == 0;
                if (!is_all_zero) {
                    break;
                }
            }
            temp_sequence = temp_vec;
        }
        history_sequences.push_back(sub_sequences);
    }

    for (auto& history: history_sequences) {
        for (long i = history.size() - 2; i >= 0; i--) {
            temp_vec = history[i + 1];
            number = history[i + 1][history[i + 1].size() - 1] + history[i][history[i].size() - 1];
            history[i].push_back(number);
            if (i == 0) {
//                cout << "Number: " << number << endl;
                sum += number;
            }
        }
    }
    cout << endl << endl;
    for (auto& history: history_sequences) {
        for (auto& vec: history) {
            for (auto& n: vec) {
                cout << n << " ";
            }
            cout << endl;
        }
        cout << endl << endl;
    }

    return sum;
}


// Part two
long sum_extrapolated_values_two(const vector<string>& inputs)
{
    vector<vector<long>> sequences;
    vector<long> temp_vec;
    long number;
    istringstream iss;
    for (const auto& input: inputs) {
        temp_vec.clear();
        iss.clear();
        iss.str(input);
        while (iss >> number) {
            temp_vec.push_back(number);
        }
        sequences.push_back(temp_vec);
    }
    long sum = 0;
    vector<vector<long>> sub_sequences;
    vector<vector<vector<long>>> history_sequences;
    sub_sequences.reserve(sequences.size());

    vector<long> temp_sequence;
    bool is_all_zero;
    for (const auto& sequence: sequences) {
        sub_sequences.clear();
        sub_sequences.push_back(sequence);
        temp_sequence = sequence;
        is_all_zero = false;
        while (!is_all_zero) {
            temp_vec.clear();
            for (int i = 0; i < temp_sequence.size() - 1; i++) {
                temp_vec.push_back(temp_sequence[i+1] - temp_sequence[i]);
            }
            sub_sequences.push_back(temp_vec);
            for (const auto& n: temp_vec) {
                is_all_zero = n == 0;
                if (!is_all_zero) {
                    break;
                }
            }
            temp_sequence = temp_vec;
        }
        history_sequences.push_back(sub_sequences);
    }

    for (auto& history: history_sequences) {
        for (long i = history.size() - 2; i >= 0; i--) {
            temp_vec = history[i + 1];
            number = history[i][0] - temp_vec[0];
            history[i][0] = number;
            if (i == 0) {
//                cout << "Number: " << number << endl;
                sum += number;
            }
        }
    }
    cout << endl << endl;
    for (auto& history: history_sequences) {
        for (auto& vec: history) {
            for (auto& n: vec) {
                cout << n << " ";
            }
            cout << endl;
        }
        cout << endl << endl;
    }

    return sum;
}
