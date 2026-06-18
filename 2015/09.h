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

/// @brief
struct Task
{
    typedef std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> WorldMap;
    inline static WorldMap map; // C++17 inline static member initialization

    static int findBestRoute(const WorldMap &p_map, const std::string &start, std::shared_ptr<std::vector<std::string>> stack = nullptr)
    {
        if (stack == nullptr)
            stack = std::make_shared<std::vector<std::string>>();
        if (stack->size() >= p_map.size() - 1)
            return 0;

        stack->push_back(start);
        int min = std::numeric_limits<int>::max();
        for (auto &entry : p_map.at(start))
        {
            const std::string &place = entry.first;
            int dist = entry.second;
            if (std::find(stack->begin(), stack->end(), place) != stack->end())
                continue;

            int yielded = findBestRoute(p_map, place, stack);
            if (yielded + dist < min)
                min = yielded + dist;
        }

        stack->pop_back();
        return min;
    }

    void run()
    {

        std::ifstream inputStream("2015/09.txt");

        if (!inputStream.is_open())
        {
            std::cerr << "Failed to open file!\n";
        }

        std::string line;
        std::regex distancePattern(R"((\w+) to (\w+) = (\d+))");
        std::smatch match;
        while (std::getline(inputStream, line))
        {
            if (std::regex_match(line, match, distancePattern))
            {
                map[match[1].str()].emplace_back(match[2].str(), std::stoi(match[3].str()));
                map[match[2].str()].emplace_back(match[1].str(), std::stoi(match[3].str()));
            }
        }
        inputStream.close();

        std::string start;
        int min = std::numeric_limits<int>::max();
        for (auto &kv : map)
        {
            const std::string &key = kv.first;
            int dist = findBestRoute(map, key);
            if (dist < min)
            {
                min = dist;
                start = key;
            }
        }

        std::cout << "Minimum distance is from " << start << " with " << min << " distance units." << std::endl;
    }

    void runPart2()
    {
    }
};

//-------------- NOTES AREA ----------------
/*

*/