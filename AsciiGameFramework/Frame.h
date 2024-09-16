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

public:
    uint GetSizeY() const { return chars.size(); }
    uint GetSizeX() const;
    void ResizeY(const uint size) { chars.resize(size); }
    void ResizeX(const uint size);
    void ReadFrameFromFile(const string& fileName, const uint screenSizeX, const uint screenSizeY);
    void ReplaceChar(const string& writenString, const char writeOverChar);
    void InsertString(const string& str, const uint xPos, const uint yPos);
    void Clear() { chars.clear(); }
};