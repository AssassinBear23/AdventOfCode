#pragma once

#include <print>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

struct Task
{
    void run()
    {
        std::ifstream inputStream("2015/01.txt");

        if (!inputStream.is_open())
        {
            std::cerr << "Failed to open input file.\n";
        }

        char c;
        bool enteredBasement = false;
        int count = 0, pos = 0, basementPos = 0;
        while (inputStream >> c)
        {
            count++;
            if (c == '(')
                pos++;
            else if (c == ')')
                pos--;

            if (pos == -1 && !enteredBasement)
            {
                enteredBasement = true;
                basementPos = count;
            }
        }
        std::cout << "Final position: " << pos << std::endl;
        std::cout << "Entered basement at position: " << basementPos << std::endl;

        inputStream.close();
    }
};