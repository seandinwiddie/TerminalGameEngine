#pragma once

#include "Config.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

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

    static void InsertString(std::vector<std::vector<unsigned char>>& frame, const string& str, const int x, const int y)
    {
        assert(y >= 0 && y < frame.size());
        assert(x >= 0 && x < frame[0].size());

        for (int i = 0; i < str.size(); ++i)
            frame[y][x + i] = str[i];
    }

    static void ReplaceChar(std::vector<std::vector<unsigned char>>& frame, const string &writenString, const unsigned char writeOverChar)
    {
        for (int y = 0; y < frame.size(); ++y)
        {
            for (int x = 0; x < frame[0].size(); ++x)
            {
                unsigned char c = frame[y][x];

                // insert score message
                if (c == writeOverChar)
                {
                    InsertString(frame, writenString, x,y);
                    x += writenString.size() - 1;
                }
            }
        }   
    }
}

