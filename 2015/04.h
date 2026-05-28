#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include "../Utils/md5.h"

/// @brief Using a key (the input), find which MD5 hash with that key + a positive interger number starts with 5 zero's. 
/// Part 2 is looking for 6 zero's
struct Task
{
    static void run()
    {
        std::string key = "bgvyzdsv";
        bool foundAnswer = false;
        int count = 0;
        while (!foundAnswer)
        {
            count++;
            std::string augmentedKey = key + std::to_string(count);
            std::string hash = MD5::toHash(augmentedKey);

            foundAnswer = hash.substr(0, 5) == "00000";
        }
        std::cout << "5 zero's: " << count << std::endl;
    }

    static void runPart2()
    {
        std::string key = "bgvyzdsv";
        bool foundAnswer = false;
        int count = 0;
        while (!foundAnswer)
        {
            count++;
            std::string augmentedKey = key + std::to_string(count);
            std::string hash = MD5::toHash(augmentedKey);

            foundAnswer = hash.substr(0, 6) == "000000";
        }
        std::cout << "6 zero's: " << count << std::endl;
    }
};

//-------------- NOTES AREA ----------------
/*

*/