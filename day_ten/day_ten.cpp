//
// Created by Maksym Kostynskyi on 10.12.2023.
//

#include "day_ten.h"
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <iostream>
#include <numeric> // For std::gcd in C++17 and later
using namespace std;

map<char, pair<char, char>> tile_direction_map = {
        {'|', {'n','s'} },
        {'-', {'e', 'w'} },
        {'L', {'n', 'e' }},
        {'J', {'n', 'w' }},
        {'7', {'s', 'w' }},
        {'F', {'s', 'e' }},
};

using Point = pair<int, int>;

map<char, Point> direction_index_map = {
        {'n', { -1, 0 }},
        {'s', { 1, 0 }},
        {'e', { 0, 1 }},
        {'w', { 0, -1 }},
};

map<char, char> direction_from_to_map = {
        {'n', 's'},
        {'s', 'n'},
        {'e', 'w'},
        {'w', 'e'},
};
// Part one
long count_steps_in_loop_one(const vector<string>& inputs)
{
    Point starting_point = {0,0};
    for (int i = 0; i < inputs.size(); i++) {
        for (int j = 0; j < inputs[i].size(); j++) {
            if (inputs[i][j] == 'S') {
                starting_point = {i, j};
                i = inputs.size();
                break;
            }
        }
    }

    char current_tile;
    char current_direction = 'w';
    Point move;
    int steps = 0;
    do {
        steps++;
        move = direction_index_map[current_direction];
        starting_point = {starting_point.first + move.first, starting_point.second + move.second};
        current_tile = inputs[starting_point.first][starting_point.second];
        current_direction = tile_direction_map[current_tile].first == direction_from_to_map[current_direction] ? tile_direction_map[current_tile].second : tile_direction_map[current_tile].first;
    } while (current_tile != 'S');

    return steps/2;
}

long count_steps_in_loop(const vector<string>& inputs)
{
    Point starting_point = {0,0};
    for (int i = 0; i < inputs.size(); i++) {
        for (int j = 0; j < inputs[i].size(); j++) {
            if (inputs[i][j] == 'S') {
                starting_point = {i, j};
                i = inputs.size();
                break;
            }
        }
    }

    char current_tile;
    char current_direction = 'n';
    Point move;
    int steps = 0;
    vector<Point> loop_points;
    map<Point, char> loop_index_tile;
    pair<vector<int>,vector<int>> path;
    do {
        steps++;
        move = direction_index_map[current_direction];
        path.first.push_back(starting_point.first);
        path.second.push_back(starting_point.second);
        starting_point = {starting_point.first + move.first, starting_point.second + move.second};
        loop_points.push_back(starting_point);
        current_tile = inputs[starting_point.first][starting_point.second];
        loop_index_tile[starting_point] = current_tile;
        current_direction = tile_direction_map[current_tile].first == direction_from_to_map[current_direction] ? tile_direction_map[current_tile].second : tile_direction_map[current_tile].first;
    } while (current_tile != 'S');

    long trailing = 0;
    cout << endl << path.first.size() / 2 << endl;
    for (int i = 0; i < path.first.size(); i++) {
        if (i == path.first.size() - 1) {
            trailing += (path.first[i] + path.first[0]) * (path.second[i] - path.second[0]);
        } else {
            trailing += (path.first[i] + path.first[i+1]) * (path.second[i] - path.second[i+1]);
        }
    }

    long area = trailing/2;

    return area - (path.first.size() / 2);
}
