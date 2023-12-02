//
// Created by Maksym Kostynskyi on 01.12.2023.
//

#include "day_two.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
using namespace  std;

int sum_games_ids(const vector<string>& input)
{
    int ids_sum = 0;
    int blue_limit = 14;
    int green_limit = 13;
    int red_limit = 12;
    int id;
    int max_red = 0;
    int max_blue = 0;
    int max_green = 0;
    int temp_amount = 0;
    string temp_color;
    std::vector<std::string> segments;
    std::vector<std::string> comma_segments;
    std::istringstream iss;
    std::string segment;
    std::string skip;
    cout << endl;
    bool is_possible = true;
    for (const string& game: input) {
        is_possible = true;
        iss.clear();
        iss.str(game);
        segments.clear();
        max_red = 0;
        max_blue = 0;
        max_green = 0;

        iss >> skip >> id;

        while (std::getline(iss, segment, ';')) {
            segments.push_back(segment);
        }

        comma_segments.clear();
        // Output the results
        for (const auto& s : segments) {
//            std::cout << s << std::endl;
            iss.clear();
            iss.str(s);
            while (std::getline(iss, segment, ',')) {
                comma_segments.push_back(segment);
            }
        }

        for (int i = 0; i < comma_segments.size(); i++) {
            iss.clear();
            iss.str(comma_segments[i]);
            if (i == 0) {
                iss >> skip;
            }
            iss >> temp_amount >> temp_color;
            if (id == 100) {
                cout << temp_color << " " << temp_amount << endl;
            }
            if (temp_color == "blue") {
//                max_blue += temp_amount;
                is_possible = temp_amount <= blue_limit;
                max_blue = max(temp_amount, max_blue);
            }
            if (temp_color == "red") {
//                max_red += temp_amount;
                is_possible = temp_amount <= red_limit;
                max_red = max(temp_amount, max_red);
            }
            if (temp_color == "green") {
//                max_green += temp_amount;
                is_possible = temp_amount <= green_limit;
                max_green = max(temp_amount, max_green);
            }

        }

       ids_sum += max_blue * max_green * max_red;
    }

    return ids_sum; // > 332 is too low
}