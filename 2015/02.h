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

/// @brief Find the surface area of a box given its dimensions presented in the input text. The order is LWH. 
/// Add a bit of extra paper, the area of the smallest side.
/// @example 3x3x2 means 2x3x3 = 18, 2x3x2 = 12 and 2x3x2 = 12, adding a 12 for smallest side means a 
struct Task
{
    static int area (int a, int b, int c){
        return 2*a*b + 2*b*c + 2*a*c + std::min(a*b, std::min(b*c, a*c));
    }

    static int ribbon (int a, int b, int c){
        return 2 * std::min(a+b, std::min(b+c, c+a)) + a * b * c;
    }


    static void run()
    {

        std::ifstream inputStream("2015/02.txt");

        if (!inputStream.is_open())
        {
            std::cerr << "Failed to open file!\n";
        }

        int a = 0, b = 0, c = 0, totalArea = 0, ribbonArea = 0;
        char sep;

        std::string line;
        while (inputStream >> a)
        {
            inputStream >> sep;
            inputStream >> b;
            inputStream >> sep;
            inputStream >> c;
        
            totalArea += area(a,b,c);
            ribbonArea += ribbon(a,b,c);
        }
        inputStream.close();
    
        std::cout << "Total Area: " << totalArea << std::endl;
        std::cout << "Total Ribbon: " << ribbonArea << std::endl;
    }
    
    static void runPart2()
    {
    }
};

//-------------- NOTES AREA ----------------
/*

*/