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

/// @brief Part 1: Find the amount of nice strings using the provided rules. Minimum of 3 vowels, contains same letter twice in a row, and no 'ab', 'cd', 'pq' or 'xy'.
/// @brief Part 2:
struct Task
{
    const std::vector<std::string> codes{
        "ab", "cd", "pq", "xy"};

    const std::vector<char> allowedVowels{
        'a', 'e', 'i', 'o', 'u'};

    bool isNice(std::string line)
    {
        char curr, prev;
        bool hasDouble = false;
        bool hasIllegal = false;
        int vowels = 0;
        for (const auto &code : codes)
        {
            if (line.find(code) != std::string::npos)
            {
                hasIllegal = true;
                return false;
            }
        }

        for (int i = 0; i < line.length(); i++)
        {
            curr = line[i];

            if (std::find(allowedVowels.begin(), allowedVowels.end(), curr) != allowedVowels.end())
                vowels++;
            if (i != 0 && curr == prev)
                hasDouble = true;

            prev = curr;
        }

        if (hasDouble && vowels >= 3)
            return true;
        return false;
    }

    bool isNice2(std::string line)
    {
        char curr, prev;
        bool hasPair = false, hasWedge = false;

        for (int i = 0; i < line.length(); i++)
        {
            curr = line[i];
            if (i > 0 && i < line.size() - 2)
                if (line.find(line.substr(i - 1, 2), i + 1) != std::string::npos)
                    hasPair = true;
            if (i > 0 && i < line.size() - 1)
                if (line[i + 1] == prev)
                    hasWedge = true;

            prev = curr;
        }

        return (hasPair && hasWedge) ? true : false;
    }

    void run()
    {
        std::ifstream inputStream("2015/05.txt");

        if (!inputStream.is_open())
        {
            std::cerr << "Failed to open file!\n";
        }

        int count1 = 0, count2 = 0;

        std::string line;
        while (std::getline(inputStream, line))
        {
            if (isNice(line))
                count1++;
        }
        inputStream.close();

        std::cout << "Nice strings count1: " << count1 << std::endl;
    }

    void runPart2()
    {
        std::ifstream inputStream("2015/05.txt");

        if (!inputStream.is_open())
        {
            std::cerr << "Failed to open file!\n";
        }

        int count1 = 0, count2 = 0;

        std::string line;
        while (std::getline(inputStream, line))
        {
            if (isNice2(line))
                count2++;
        }
        inputStream.close();

        std::cout << "Nice strings count2: " << count2 << std::endl;
    }
};

//-------------- NOTES AREA ----------------
/*

*/