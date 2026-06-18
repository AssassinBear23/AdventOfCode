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

/// @brief Get the amount of characters in code where "" is already 2 character,
/// and subtract from that the amount of chracters in the string data where "\x32" is a ASCII code, so that would be one character in string data.
struct Task
{
    int _codeCharacterCount = 0;
    int _stringCharacterCount = 0;

    int GetCodeCharacterCount(std::string line)
    {
        return line.length();
    }

    int GetStringCharacterCount(std::string line)
    {

        std::regex hexicodePattern(R"(\\x([0-9A-Fa-f]{2}))");
        std::regex quoteCharacterPattern(R"((\\"))");
        std::regex backslashPatten(R"((\\{2}))");

        std::smatch match;

        line = line.substr(1, line.size() - 2); // Remove container quote characters

        while (std::regex_search(line, match, hexicodePattern)) // Replace hexcode characters
        {
            try
            {
                int value = std::stoi(match[1].str(), nullptr, 16);
                char c = static_cast<char>(value);
                line.replace(match.position(), match.length(), std::string(1, c));
            }
            catch (const std::invalid_argument &e)
            {
                std::cout << "Invalid Hex: " << match[1] << std::endl;
            }
            catch (const std::out_of_range &e)
            {
                std::cout << "Out of hex range: " << match[1] << std::endl;
            }
        }

        line = std::regex_replace(line, quoteCharacterPattern, "\""); // Replace quote characters
        line = std::regex_replace(line, backslashPatten, "\\");       // Replace backslash characters

        std::cout << "End line:      " << line << std::endl;

        return line.length();
    }

    void run()
    {
        std::ifstream inputStream("2015/08.txt");

        if (!inputStream.is_open())
        {
            std::cerr << "Failed to open file!\n";
        }

        std::string line;
        while (std::getline(inputStream, line))
        {
            std::cout << "Starting line: " << line << std::endl;
            _codeCharacterCount += GetCodeCharacterCount(line);
            _stringCharacterCount += GetStringCharacterCount(line);
        }
        inputStream.close();

        std::printf("Code Characters: %i\nString Characters: %i\n", _codeCharacterCount, _stringCharacterCount);
        std::printf("Answer: %i\n", (_codeCharacterCount - _stringCharacterCount));
    }

    int GetEncodeCharacterAmount(std::string line)
    {
        int score = 0;

        for (char i : line)
        {
            if (i == '\\' || i == '\"')
                score++;
                
        }
        score += 2;
        return score;
    }

    void runPart2()
    {
        std::ifstream inputStream("2015/08.txt");

        if (!inputStream.is_open())
        {
            std::cerr << "Failed to open file!\n";
        }

        std::string line;
        int score = 0;
        while (std::getline(inputStream, line))
        {
            score += GetEncodeCharacterAmount(line);
        }
        std::cout << score << "\n";
        inputStream.close();
    }
};

//-------------- NOTES AREA ----------------
/*

*/