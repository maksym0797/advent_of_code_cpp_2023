//
// Created by Maksym Kostynskyi on 08.12.2023.
//

#include "day_eight.h"
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <iostream>
#include <numeric> // For std::gcd in C++17 and later
using namespace std;
// Function to find GCD of two numbers

// Function to find LCM of two numbers
long lcm(long a, long b) {
    return a / gcd(a, b) * b; // Multiplying after division to prevent overflow
}

// Function to find LCM of a list of numbers
long findLCM(const std::vector<long>& numbers) {
    long result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        result = lcm(result, numbers[i]);
    }
    return result;
}


using BiTree = map<string, pair<string, string>>;

long count_steps_to_reach(const vector<string>& inputs)
{
    string moves = inputs[0];
    BiTree tree;
    string temp;
    vector<string> start_nodes;
//    cout << endl;
    for (int i = 2; i < inputs.size(); ++i) {
        temp = inputs[i];
        if (temp.substr(0, 3)[2] == 'A') {
            start_nodes.push_back(temp.substr(0, 3));
        }
//        cout << temp.substr(0, 3) << " -> " << temp.substr(7, 3) << "<>" << temp.substr(12, 3) << endl;
        tree[temp.substr(0, 3)] = {temp.substr(7, 3), temp.substr(12, 3)};
    }
//    string current_node;
    string end_node = "ZZZ";
    int move_ind = 0;
    long long steps = 0;
    bool all_got_end = false;
    vector<long> steps_list;
    vector<int> visited_indexes;
    map<int, long> steps_map;

        temp = "";
        for (auto & start_node : start_nodes) {
            steps = 0;
            while (start_node[2] != 'Z') {
                steps++;
                string current_node = start_node;
                start_node = moves[move_ind] == 'L' ? tree[current_node].first : tree[current_node].second;
                if (move_ind == moves.length() - 1) {
                    move_ind = 0;
                    continue;
                }
                move_ind++;
            }
            steps_list.push_back(steps);
        }

    cout << endl;
    steps = 1;
    for (auto s: steps_list) {
        cout << "steps: " << s << endl;
        steps *= s;
    }

    return findLCM(steps_list);
}
// > 724195920198
// < 8 811 050 362 409
// < 52866302174454