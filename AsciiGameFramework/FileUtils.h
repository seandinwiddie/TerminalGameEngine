#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using string = std::string;

namespace FileUtils
{
    static void ReadFrameFromFile(const string& fileName, const int screenSizeX, const int screenSizeY, std::vector<std::vector<unsigned char>>& frame)
    {
        std::ifstream file(fileName, std::ios::binary);
        if (!file)
        {
            std::cerr << "Error opening file." << std::endl;
            return;
        }

        // Resize the vector to hold the rows
        frame.resize(screenSizeY);

        //Read the data into the vector
        for (int m = 0; m < screenSizeY; ++m)
        {
            frame[m].resize(screenSizeX);

            for (int n = 0; n < screenSizeX; ++n)
            {
                unsigned char c = file.get();

                //ignore invisible characters
                if (c == '\n' || c == '\r' || c == '\t' || c == '\0')
                {
                    --n;
                    continue;
                }
                frame[m][n] = c;
            }
        }

        std::reverse(frame.begin(), frame.end());
    }
}

