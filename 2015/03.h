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

/// TODO: put a small description of the task
struct Task
{
    static void run()
    {
        std::ifstream inputStream("2015/03.txt");

        if (!inputStream.is_open())
        {
            std::cerr << "Failed to open file!\n";
        }

        int x = 0, y = 0 , robotx = 0, roboty = 0;
        std::vector<int> map {0};

        char dir, robotDir;
        while (inputStream >> dir)
        {
            switch (dir)
            {
                case '^': y++; break;
                case 'v': y--; break;
                case '>': x++; break;
                case '<': x--; break;
            }

            inputStream >> robotDir;

            switch (robotDir)
            {
                case '^': roboty++; break;
                case 'v': roboty--; break;
                case '>': robotx++; break;
                case '<': robotx--; break;
            }

            int loc = (x << 8) + y;
            if(std::find(map.begin(),map.end(), loc) == map.end())
                map.push_back(loc);

            loc = (robotx << 8) + roboty;
            if (std::find(map.begin(), map.end(), loc) == map.end())
                map.push_back(loc);
        }
        inputStream.close();

        std::cout << "Total houses visited: " << map.size() << std::endl;
    }

    static void runPart2()
    {
    }
};

//-------------- NOTES AREA ----------------
/*

*/