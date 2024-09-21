#pragma once

#include "Config.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <cassert>
#include <string>

using string = std::string;

class Frame
{
public:
    std::vector<std::vector<char>> chars;
    std::vector<std::vector<int>> colors;

public:
    uint GetSizeY() const { return chars.size(); }
    uint GetSizeX() const;
    void ResizeY(uint size) { chars.resize(size); colors.resize(size); }
    void ResizeX(uint size);
    void ReadFrameFromFile(const string& fileName, uint screenSizeX, uint screenSizeY);
    void ReplaceChar(const string& writenString, char writeOverChar);
    void InsertString(const string& str, uint xPos, uint yPos);
    void Clear() { chars.clear(); }
};