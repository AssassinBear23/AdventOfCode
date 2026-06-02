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
    enum instruction
    {
        Assign,
        And,
        Or,
        Not,
        RightShift,
        LeftShift
    };

    std::unordered_map<std::string, uint16_t> variableRegistery;
    std::unordered_map<std::string, std::vector<std::string>> dependencyRegistry;
    std::unordered_map<std::string, instruction> instructionRegistry;

    int applyInstruction(const instruction &m_instruction, const std::vector<int> &values)
    {
        switch (m_instruction)
        {
        case Assign:
            return values[0];
        case And:
            return values[0] & values[1];
        case Not:
            return ~values[0];
        case Or:
            return values[0] | values[1];
        case RightShift:
            return values[0] >> values[1];
        case LeftShift:
            return values[0] << values[1];
        default:
            return 0;
        };
    }

    void calculateWire(
        const std::string wire,
        std::unordered_map<std::string, uint16_t> &m_variableRegistry,
        const std::unordered_map<std::string, std::vector<std::string>> &m_dependencyRegistry,
        const std::unordered_map<std::string, instruction> &m_instructionRegistry)
    {
        if (m_variableRegistry.find(wire) != m_variableRegistry.end())
            return;

        // Calculate dependencies
        std::vector<int> values;
        for (auto &dependency : m_dependencyRegistry.at(wire))
        {
            if (dependency.empty() || dependency.find_first_of("0123456789") != std::string::npos)
            {
                values.push_back(std::stoi(dependency));
                continue;
            }
            calculateWire(dependency, m_variableRegistry, m_dependencyRegistry, m_instructionRegistry);
            values.push_back(m_variableRegistry.at(dependency));
        }

        m_variableRegistry[wire] = applyInstruction(m_instructionRegistry.at(wire), values);
    }

    void run()
    {
        std::ifstream inputStream("2015/07.txt");

        if (!inputStream.is_open())
        {
            std::cerr << "Failed to open file!\n";
        }

        std::regex assignPattern(R"((\d+)\s->\s([a-z]+))");
        std::regex assignVarPattern(R"(([a-z]+)\s->\s([a-z]+))");
        std::regex andPattern(R"(([a-z]+)\sAND\s([a-z]+)\s->\s([a-z]+))");
        std::regex andNumToVarPattern(R"((\d+)\sAND\s([a-z]+)\s->\s([a-z]+))");
        std::regex rightShiftPattern(R"(([a-z]+)\sRSHIFT\s(\d+)\s->\s([a-z]+))");
        std::regex leftShiftPattern(R"(([a-z]+)\sLSHIFT\s(\d+)\s->\s([a-z]+))");
        std::regex notPattern(R"(NOT\s([a-z]+)\s->\s([a-z]+))");
        std::regex orPattern(R"(([a-z]+)\sOR\s([a-z]+)\s->\s([a-z]+))");

        std::printf("Starting\n");

        std::smatch match;
        std::string line;
        while (std::getline(inputStream, line))
        {
            if (std::regex_match(line, match, assignPattern))
                variableRegistery[match[2].str()] = std::stoi(match[1].str());
            else if (std::regex_match(line, match, assignVarPattern))
            {
                dependencyRegistry[match[2].str()] = std::vector<std::string>{match[1].str()};
                instructionRegistry[match[2].str()] = Assign;
            }
            if (std::regex_match(line, match, andPattern))
            {
                dependencyRegistry[match[3].str()] = std::vector<std::string>{match[1].str(), match[2].str()};
                instructionRegistry[match[3].str()] = And;
            }
            else if (std::regex_match(line, match, andNumToVarPattern))
            {
                dependencyRegistry[match[3].str()] = std::vector<std::string>{match[2].str(), match[1].str()};
                instructionRegistry[match[3].str()] = And;
            }
            if (std::regex_match(line, match, rightShiftPattern))
            {
                dependencyRegistry[match[3].str()] = std::vector<std::string>{match[1].str(), match[2].str()};
                instructionRegistry[match[3].str()] = RightShift;
            }
            if (std::regex_match(line, match, leftShiftPattern))
            {
                dependencyRegistry[match[3].str()] = std::vector<std::string>{match[1].str(), match[2].str()};
                instructionRegistry[match[3].str()] = LeftShift;
            }
            if (std::regex_match(line, match, orPattern))
            {
                dependencyRegistry[match[3].str()] = std::vector<std::string>{match[1].str(), match[2].str()};
                instructionRegistry[match[3].str()] = Or;
            }
            if (std::regex_match(line, match, notPattern))
            {
                dependencyRegistry[match[2].str()] = std::vector<std::string>{match[1].str()};
                instructionRegistry[match[2].str()] = Not;
            }
        }
        calculateWire("a", variableRegistery, dependencyRegistry, instructionRegistry);
        std::printf("Value of wire a: %i\n", variableRegistery.at("a"));
        inputStream.close();
    }

    void runPart2()
    {
        int orgValueA = variableRegistery.at("a");
        for (const auto &connection : dependencyRegistry)
        {
            auto it = variableRegistery.find(connection.first);
            if (it != variableRegistery.end())
                variableRegistery.erase(it);
        }

        variableRegistery["b"] = orgValueA;
        calculateWire("a", variableRegistery, dependencyRegistry, instructionRegistry);
        std::printf("New value of wire a: %i\n", variableRegistery.at("a"));
    }
};

//-------------- NOTES AREA ----------------
/*

*/