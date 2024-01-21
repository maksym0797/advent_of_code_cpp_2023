//
//  main.cpp
//  advent_of_code_2023_cpp
//
//  Created by Maksym Kostynskyi on 01.12.2023.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "day_one/day_one.hpp"
#include "day_two/day_two.h"
#include "day_three/day_three.h"
#include "day_four/day_four.h"
#include "day_five/day_five.h"
#include "day_six/day_six.h"
#include "day_seven/day_seven.h"
#include "day_eight/day_eight.h"
#include "day_nine/day_nine.h"
#include "day_ten/day_ten.h"
#include "day_eleven/day_eleven.h"



using namespace std;

int main(int argc, const char *argv[])
{
    fstream inputFile;
    inputFile.open("/Users/Maksym_Kostynskyi/Code/playground/advent_of_code_2023_cpp/advent_of_code_2023_cpp/input.txt", ios::in);
    if (inputFile.is_open())
    {
        string tempStr;
        vector<string> inputList;
        while (getline(inputFile, tempStr))
        {
            inputList.push_back(tempStr);
        }
        cout << "The result is: " << sum_galaxies_lengths(inputList) << endl;
    }
    else
    {
        cout << "Error, cannot open input file" << endl;
    }

    return 0;
}
