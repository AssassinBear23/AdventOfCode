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

/// @brief Pt1: Using instructions turn on/off or toggle lights in specific ranges using given coordinate pairs. Answer is the amount of lights turned on.
struct Task
{
    std::vector<uint16_t> enabledLights;

    bool turnOnLight(uint16_t coordinate)
    {
        if (std::find(enabledLights.begin(), enabledLights.end(), coordinate) == enabledLights.end())
        {
            enabledLights.push_back(coordinate);
            return true;
        }
        return false;
    }

    void turnOffLight(uint16_t coordinate)
    {
        auto it = std::find(enabledLights.begin(), enabledLights.end(), coordinate);
        if (it != enabledLights.end())
            enabledLights.erase(std::remove(enabledLights.begin(), enabledLights.end(), coordinate), enabledLights.end());
    }

    void toggleLight(uint16_t coordinate)
    {
        if (!turnOnLight(coordinate))
            turnOffLight(coordinate);
    }

    void processInput(std::string line)
    {
        enum command
        {
            on,
            off,
            toggle
        };
        command comm;
        int x1, x2, y1, y2;

        if (line.find("turn") != std::string::npos) // search for "turn", true if found.
        {
            if (line.find("on") != std::string::npos) // found "on" in string.
            {
                comm = command::on;
                line.erase(0, 8);
            }
            else // "on" not found so its off.
            {
                comm = command::off;
                line.erase(0, 9);
            }
        }
        else // toggle command
        {
            comm = command::toggle;
            line.erase(0, 7);
        }

        line.erase(line.find("through"), 8);

        x1 = std::stoi(line);
        line.erase(0, line.find(',') + 1);
        y1 = std::stoi(line);
        line.erase(0, line.find(std::to_string(y1)) + 1);
        x2 = std::stoi(line);
        line.erase(0, line.find(',') + 1);
        y2 = std::stoi(line);

        switch (comm)
        {
        case command::on:
            printf("Turning lights on in range: <%i, %i> to <%i, %i>. Currently %zu are on.\n", x1, y1, x2, y2, enabledLights.size());
            break;
        case command::off:
            printf("Turning lights off in range: <%i, %i> to <%i, %i>. Currently %zu are on.\n", x1, y1, x2, y2, enabledLights.size());
            break;
        case command::toggle:
            printf("Toggling lights in range: <%i, %i> to <%i, %i>. Currently %zu are on.\n", x1, y1, x2, y2, enabledLights.size());
            break;
        default:
            break;
        }

        for (int i = x1; i <= x2; i++)
        {
            for (int j = y1; j <= y2; j++)
            {
                uint16_t coordinate = (i * 1000) + j;
                switch (comm)
                {
                case command::on:
                    turnOnLight(coordinate);
                    break;
                case command::off:
                    // printf("Turning off light at coordinate: <%i, %i>.\n", i, j);
                    turnOffLight(coordinate);
                    break;
                case command::toggle:
                    // printf("Toggling light at coordinate: <%i, %i>.\n", i, j);
                    toggleLight(coordinate);
                    break;
                default:
                    std::printf("Error during processing, no input command set.");
                    break;
                }
            }
        }
    }

    void
    run()
    {
        std::ifstream inputStream("2015/06.txt");

        if (!inputStream.is_open())
            std::cerr << "Failed to open file!\n";

        int cnt = 0;

        std::string line;
        while (std::getline(inputStream, line))
        {
            cnt++;
            processInput(line);
        }
        inputStream.close();
        std::printf("Processed %i lines.\n", cnt);

        std::printf("%zu lights are on.\n", enabledLights.size());
    }

    void runPart2()
    {
    }
};

//-------------- NOTES AREA ----------------
/*
Because your neighbors keep defeating you in the holiday house decorating contest year after year, you've decided to deploy one million lights in a 1000x1000 grid.

Furthermore, because you've been especially nice this year, Santa has mailed you instructions on how to display the ideal lighting configuration.

Lights in your grid are numbered from 0 to 999 in each direction; the lights at each corner are at 0,0, 0,999, 999,999, and 999,0. The instructions include whether to turn on, turn off, or toggle various inclusive ranges given as coordinate pairs. Each coordinate pair represents opposite corners of a rectangle, inclusive; a coordinate pair like 0,0 through 2,2 therefore refers to 9 lights in a 3x3 square. The lights all start turned off.

To defeat your neighbors this year, all you have to do is set up your lights by doing the instructions Santa sent you in order.

For example:

turn on 0,0 through 999,999 would turn on (or leave on) every light.
toggle 0,0 through 999,0 would toggle the first line of 1000 lights, turning off the ones that were on, and turning on the ones that were off.
turn off 499,499 through 500,500 would turn off (or leave off) the middle four lights.
After following the instructions, how many lights are lit?
*/