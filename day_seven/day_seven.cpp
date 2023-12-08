//
// Created by Maksym Kostynskyi on 07.12.2023.
//

#include "day_seven.h"
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
#include <iostream>
using namespace std;

map<char, int> cards_strength = {
        {'A', 13},
        {'K', 12},
        {'Q', 11},
        {'T', 10},
        {'9', 9},
        {'8', 8},
        {'7', 7},
        {'6', 6},
        {'5', 5},
        {'4', 4},
        {'3', 3},
        {'2', 2},
        {'J', 1},
};

set<char> str_to_set_without_j(string& str) {
    std::set<char> charSet;

    for (char c : str) {
        if (c == 'J') {
            continue;
        }
        charSet.insert(c);
    }

    return charSet;
}

struct GameHand {
    string hand;
    long bid;
    int get_hand_type() {
        set<char> cards = str_to_set_without_j(hand);
        int card_count;
        map<char, int> cards_occur;
        int j_count = std::count(hand.begin(), hand.end(), 'J');
        bool hasJ = j_count > 0;
        if (cards.size() <= 1) {
            return 6;
        }

        int max_card_count = 0;
        string temp_str;
        for (const char& c: cards) {
            card_count = std::count(hand.begin(), hand.end(), c);
            cards_occur[c] = card_count;
            max_card_count = max(max_card_count, card_count);
            temp_str += c;
        }

        if (max_card_count >= 5 || max_card_count + j_count >= 5) {
            return 6;
        }

        if (max_card_count == 4) {
            return hasJ ? 6 : 5;
        }

        if (max_card_count == 3) {
            if (hasJ) {
                return j_count > 1 ? 6 : 5;
            }

            // three
            if (cards.size() > 2) {
                return 3;
            }

            // full house
            return 4;
        }
        if (max_card_count == 2) {
            if (j_count >= 2) {
                return ((j_count > 2) ? 6 : 5);
            }
            if (hasJ) {
                if (temp_str.size() == 2 && j_count == 1) {
                    return cards_occur[temp_str[0]] == 2 && cards_occur[temp_str[1]] == 2 ? 4 : 3;
                }
                return 3;
            }

            if (temp_str.size() == 3) {
                return 2;
            }

            return 1;
        }

        if (j_count >= 3) {
            return 5;
        }

        if (j_count == 2) {
            return 3;
        }

        if (j_count == 1) {
            return 1;
        }



//        // High card
//        if (cards_size == hand.size()) {
//            return 0;
//        }
//        // Five
//        if (cards_size == 1) {
//            return 6;
//        }
//        // four or full house
//        if (cards_size == 2) {
//            int max_card_count = 0;
//            for (const char& c: hand) {
//                card_count = std::count(hand.begin(), hand.end(), c) + j_count;
//                max_card_count = max(max_card_count, card_count);
//            }
//
//            return max_card_count == 4 || max_card_count == 1 ? 5 : 4;
//        }
//
//        // three or two pair
//        if (cards_size == 3) {
//            int max_size = 0;
//            int points = 0;
//            for (int i = 0; i < hand.size() - 1; i++) {
//                card_count = std::count(hand.begin(), hand.end(), hand[i]) + j_count;
//
//                points = card_count == 2 ? 2 : 3;
//                max_size = max(max_size, points);
//            }
//
//            return max_size;
//
//        }
//
//        // one pair
//        if (cards_size == 4) {
//            return 1;
//        }

        return 0;
    }
};

bool compare_game_hands(GameHand& handA, GameHand& handB)
{
    int typeA = handA.get_hand_type();
    int typeB = handB.get_hand_type();
    if (typeA != typeB) {
        return typeA > typeB;
    }
    for (int i = 0; i < handA.hand.size(); i++) {
        if (cards_strength[handA.hand[i]] == cards_strength[handB.hand[i]]) {
            continue;
        }
        return cards_strength[handA.hand[i]] > cards_strength[handB.hand[i]];
    }
    return false;
}

long total_winnings_hands(const vector<string>& inputs)
{
    vector<GameHand> game_hands;
    istringstream iss;
    long bid;
    string hand;
    for (const string& str: inputs) {
        iss.clear();
        iss.str(str);
        iss >> hand >> bid;
        game_hands.push_back(GameHand({hand, bid}));
    }
    sort(game_hands.begin(), game_hands.end(), compare_game_hands);
    reverse(game_hands.begin(), game_hands.end());
    cout << endl;
    long result = 0;
    for (int i = 0; i < game_hands.size(); i++) {
        cout << "Hand: " << game_hands[i].hand << " Bid: " << game_hands[i].bid << " Type: " << game_hands[i].get_hand_type() << endl;
        result += game_hands[i].bid * (i+1);
    }
    return result; // < 255892723
}

// 255892723

// 254837398
// 254312798
// 253929197