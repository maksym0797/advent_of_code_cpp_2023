//
// Created by Maksym Kostynskyi on 04.12.2023.
//

#include "day_four.h"
#include <string>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace  std;
// Function to fill set with numbers from string
auto fillVector = [](const std::string& str, std::set<int>& vec) {
    std::istringstream iss(str);
    int number;
    while (iss >> number) {
        vec.insert(number);
    }
};
// Part One
long total_scratchcards_points_one(const vector<string>& inputs)
{
    long total_points = 0;
    set<int> winning_numbers;
    set<int> gained_numbers;
    std::set<int> intersection;
    string input;

    for (const auto& temp : inputs) {
        input = temp;
        winning_numbers.clear();
        gained_numbers.clear();
        intersection.clear();
        // Remove "Card 1:" part
        size_t colonPos = input.find(':');
        if (colonPos != std::string::npos) {
            input = input.substr(colonPos + 1);
        }

        // Find the position of '|'
        size_t pipePos = input.find('|');
        std::string firstPart = input.substr(0, pipePos);
        std::string secondPart = input.substr(pipePos + 1);
        fillVector(firstPart, winning_numbers);
        fillVector(secondPart, gained_numbers);
        std::set_intersection(winning_numbers.begin(), winning_numbers.end(),
                              gained_numbers.begin(), gained_numbers.end(),
                              std::inserter(intersection, intersection.begin()));
        if (!intersection.empty()) {
            total_points += pow(2, intersection.size() - 1);
        }
    }

    return total_points;
}


// Part Two
long total_scratchcards_points(const vector<string>& inputs)
{
    long total_points = 0;
    set<int> winning_numbers;
    set<int> gained_numbers;
    std::set<int> intersection;
    string input;
    map<int, int> cards_map;
    for (int i = 1; i <= inputs.size(); i++) {
        cards_map[i] = 1;
    }
    int card_number;
    for (int i = 0; i < inputs.size(); i++) {
        card_number = i + 1;
        input = inputs[i];
        winning_numbers.clear();
        gained_numbers.clear();
        intersection.clear();
        // Remove "Card 1:" part
        size_t colonPos = input.find(':');
        if (colonPos != std::string::npos) {
            input = input.substr(colonPos + 1);
        }

        // Find the position of '|'
        size_t pipePos = input.find('|');
        std::string firstPart = input.substr(0, pipePos);
        std::string secondPart = input.substr(pipePos + 1);
        fillVector(firstPart, winning_numbers);
        fillVector(secondPart, gained_numbers);
        std::set_intersection(winning_numbers.begin(), winning_numbers.end(),
                              gained_numbers.begin(), gained_numbers.end(),
                              std::inserter(intersection, intersection.begin()));
        if (!intersection.empty()) {
            for (int j = 1; j <= intersection.size(); j++) {
                cards_map[card_number + j] += cards_map[card_number];
            }
        }
    }

    for (const auto& card: cards_map) {
        total_points += card.second;
    }

    return total_points;
}