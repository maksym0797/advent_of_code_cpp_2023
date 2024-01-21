//
// Created by Maksym Kostynskyi on 15.12.2023.
//

#include "day_eleven.h"
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <iostream>
#include <numeric> // For std::gcd in C++17 and later
using namespace std;
using Point = pair<int, int>;


long manhattan_distance(Point point1, Point point2, long empty_rows, long empty_columns)
{
    return abs(point2.first - point1.first) + abs(point2.second - point1.second) + (empty_rows + empty_columns) * 999999;
}

long sum_galaxies_lengths(const vector<string>& inputs)
{
    vector<Point> galaxies;
    vector<int> empty_rows;
    vector<int> empty_columns;
    long distance_sum = 0;

    for (int i = 0; i < inputs.size(); i++) {
        bool is_empty = true;
        for (int j = 0; j < inputs[i].size(); j++) {
            if (inputs[i][j] == '#') {
                is_empty = false;
                galaxies.push_back(make_pair(i, j));
            }
        }
        if (is_empty) {
            empty_rows.push_back(i);
        }
    }

    for (int i = 0; i < inputs.size(); i++) {
        bool is_empty = true;
        for (int j = 0; j < inputs[i].size(); j++) {
            if (inputs[j][i] == '#') {
                is_empty = false;
                break;
            }
        }
        if (is_empty) {
            empty_columns.push_back(i);
        }
    }

    vector<int> temp_empty_rows;
    vector<int> temp_empty_columns;
cout << endl;
    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            int lower_bound = galaxies[i].first < galaxies[j].first ? galaxies[i].first : galaxies[j].first;
            int upper_bound = galaxies[i].first > galaxies[j].first ? galaxies[i].first : galaxies[j].first;
            temp_empty_rows.clear();
            temp_empty_columns.clear();
            std::copy_if(empty_rows.begin(), empty_rows.end(), std::back_inserter(temp_empty_rows),
                         [lower_bound, upper_bound](int x) {
                             return x > lower_bound && x < upper_bound;
                         });
            lower_bound = galaxies[i].second < galaxies[j].second ? galaxies[i].second : galaxies[j].second;
            upper_bound = galaxies[i].second > galaxies[j].second ? galaxies[i].second : galaxies[j].second;
            std::copy_if(empty_columns.begin(), empty_columns.end(), std::back_inserter(temp_empty_columns),
                         [lower_bound, upper_bound](int x) {
                             return x > lower_bound && x < upper_bound;
                         });
            if (i == 2 && j == 5) {
                cout << "Galaxies: " << i + 1 << " <-> " << j + 1 << " >> distance: " << manhattan_distance(
                        galaxies[i],
                        galaxies[j],
                        temp_empty_rows.size(),
                        temp_empty_columns.size()
                ) << " rows: " << temp_empty_rows.size() << " columns: " << temp_empty_columns.size() << endl;
            }
            distance_sum += manhattan_distance(
                    galaxies[i],
                    galaxies[j],
                    temp_empty_rows.size(),
                    temp_empty_columns.size()
            );
        }
    }


    return distance_sum;
}
