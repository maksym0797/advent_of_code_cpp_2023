//
// Created by Maksym Kostynskyi on 05.12.2023.
//

#include "day_five.h"
#include <string>
#include <algorithm>
#include <tuple>
#include <vector>
#include <set>
#include <optional>
#include <utility>
#include <sstream>
#include <iostream>
#include <map>
#include <iterator>

using namespace std;
bool isInRange(long long x, long long lower, long long upper) {
    return x >= lower && x < upper;
}
// part ONe
long find_lowest_location_one(const vector<string>& inputs)
{
    vector<long long> seeds;
    vector<long long> temp_vec;
    std::istringstream iss(inputs[0]);
    long long number;
    iss.ignore(7);
    cout << endl;
    while (iss >> number) {
        seeds.push_back(number);
    }
    cout << endl;

    iss.clear();
    long long dest_start, source_start, range_len;
    map<long long, long long> almanac_map;
    vector<string> maps;
    for (int i = 3; i < inputs.size(); i+=2) {
        almanac_map.clear();
        temp_vec.clear();
        maps.clear();
        if (inputs[i].find("to") != string::npos || inputs[i].empty()) {
            cout << "ALARM" << endl;
        }
        while (i < inputs.size() && !inputs[i].empty()) {
           maps.push_back(inputs[i]);
           i++;
        }
        for (const auto& seed: seeds) {
            for(const string& str: maps) {
                iss.clear();
                iss.str(str);
                iss >> dest_start >> source_start >> range_len;
                if (isInRange(seed, source_start, (source_start + range_len))) {
                    almanac_map[seed] = seed + (dest_start - source_start);
//                    temp_vec.push_back(seed + (dest_start - source_start));
//                    seeds.erase(std::remove(seeds.begin(), seeds.end(), seed), seeds.end());
                    break;
                }
            }
        }
        for (const auto& seed: seeds) {
            temp_vec.push_back(almanac_map.contains(seed) ? almanac_map[seed] : seed);
        }
        seeds = temp_vec;
    }

    long long min_seed = LONG_LONG_MAX;

    for (const auto& seed: seeds) {
        min_seed = min(seed, min_seed);
    }

    return min_seed; // < 2743737607
}
using Range = std::pair<long, long>;
bool doRangesIntersect(const Range& r1, const Range& r2) {
    return std::max(r1.first, r2.first) < std::min(r1.second, r2.second);
}

std::tuple<std::optional<Range>, std::optional<Range>, std::optional<Range>>
findIntersectionAndDifference(const Range range1, const Range range2) {
    // Find the intersection
    long start = std::max(range1.first, range2.first);
    long end = std::min(range1.second, range2.second);

    std::optional<Range> intersection;
    std::optional<Range> diff1, diff2;

    if (start < end) {
        // Intersection exists
        intersection = std::make_pair(start, end);

        // Calculate the non-intersecting parts
        if (range1.first < start) diff1 = std::make_pair(range1.first, start);
        if (end < range1.second) {
            diff2 = std::make_pair(end, range1.second);
        }
    }

    return {intersection, diff1, diff2};
}
long find_lowest_location(const vector<string>& inputs)
{
    set<long> seeds;
    vector<Range> seeds_ranges;
    vector<Range> seeds_ranges_copy;
    vector<Range> temp_ranges;
    vector<long> temp_vec;
    set<Range> make_unique_set;
    std::istringstream iss(inputs[0]);
    long number;
    iss.ignore(7);
    cout << endl;
    while (iss >> number) {
        temp_vec.push_back(number);
    }

    for (int i = 0; i < temp_vec.size(); i+=2) {
        seeds_ranges.push_back(Range({temp_vec[i], temp_vec[i] + temp_vec[i+1]}));
//        for (long j = temp_vec[i]; j < temp_vec[i] + temp_vec[i+1]; j++) {
//            seeds.push_back(j);
//        }
    }

    cout << endl;

    iss.clear();
    long dest_start, source_start, range_len;
    map<long, long> almanac_map;
    vector<string> maps;
    vector<Range> visited;
    for (int i = 3; i < inputs.size(); i+=2) {
        almanac_map.clear();
        temp_vec.clear();
        temp_ranges.clear();
        seeds_ranges_copy = seeds_ranges;
        maps.clear();
        if (inputs[i].find("to") != string::npos || inputs[i].empty()) {
            cout << "ALARM" << endl;
        }
        while (i < inputs.size() && !inputs[i].empty()) {
            maps.push_back(inputs[i]);
            i++;
        }
        visited.clear();
        for (long seed_ind = 0; seed_ind < seeds_ranges_copy.size(); seed_ind++) {
            Range seed_range = seeds_ranges_copy[seed_ind];
            auto it = std::find_if(visited.begin(), visited.end(), [seed_range](const Range& range) {
                return range.first == seed_range.first && range.second == seed_range.second;
            });
            if (it != visited.end()) {
                continue;
            }
            long in_val = seed_range.first;
            auto s_it = std::find_if(temp_ranges.begin(), temp_ranges.end(), [in_val](const Range& range) {
                return range.first == in_val;
            });
            if (s_it != temp_ranges.end()) {
                continue;
            }
            for(const string& str: maps) {
                iss.clear();
                iss.str(str);
                iss >> dest_start >> source_start >> range_len;
                if (source_start == 77 && seed_range.first == 74) {
                    cout << "KARAMBA";
                }
                Range map_range = Range{source_start, source_start+range_len};
                if (doRangesIntersect(seed_range, map_range)) {
                    auto [intersection, diff1, diff2] = findIntersectionAndDifference(seed_range, map_range);
                    long new_start = dest_start + (intersection->first - source_start);
//                    if (new_start == 46) {
//                        cout << "KARAMBA";
//                    }
                    temp_ranges.push_back(Range({new_start, (dest_start+range_len) - ((source_start+range_len) - intersection->second)}));
                    visited.push_back(seed_range);
                    if (diff1) {
                        if (diff1->first >= 436814) {
                            cout << "KARAMBA";
                        }
                        seeds_ranges_copy.push_back(Range({diff1->first, diff1->second}));
                    }

                    if (diff2) {
                        if (diff2->first >= 436814) {
                            cout << "KARAMBA";
                        }
                        seeds_ranges_copy.push_back(Range({diff2->first, diff2->second}));
                    }


// [[46..56, 82..85, 60..61], [94..97, 86..90, 56..60]]
//                    temp_vec.push_back(seed + (dest_start - source_start));
//                    seeds.erase(std::remove(seeds.begin(), seeds.end(), seed), seeds.end());
                    break;
                }
            }
        }

        seeds_ranges.clear();
        make_unique_set.clear();
        for (const auto& seed_range: temp_ranges) {
            make_unique_set.insert(seed_range);
        }

        for (const auto& seed_range: seeds_ranges_copy) {
            auto it = std::find_if(visited.begin(), visited.end(), [seed_range](const Range& range) {
                return range.first == seed_range.first && range.second == seed_range.second;
            });
            if (it != visited.end()) {
                continue;
            }
            make_unique_set.insert(seed_range);
        }

        for (const auto& seed_range: make_unique_set) {
            seeds_ranges.push_back(seed_range);
        }

        for (const auto& seed_range: seeds_ranges) {
            cout << seed_range.first << " " << seed_range.second << endl;
        }
        cout << endl;

//        cout << floor(((double)i) / ((double)inputs.size()) * 100) << "% ";
    }

    long min_seed = LONG_LONG_MAX;

    for (const auto& seed_range: seeds_ranges) {
        cout << seed_range.first << " " << seed_range.second << endl;
        min_seed = min(seed_range.first, min_seed);
    }

    return min_seed; // < 2743737607
}
// 1087133974
// 2520868448
// 2743737607
// 600279879 !!!
