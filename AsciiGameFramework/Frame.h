#pragma once

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
    unsigned int GetSizeY() const { return chars.size(); }
    unsigned int GetSizeX() const;
    void ResizeY(const unsigned int size) { chars.resize(size); }
    void ResizeX(const unsigned int size);
    void ReadFrameFromFile(const string& fileName, const int screenSizeX, const int screenSizeY);
    void ReplaceChar(const string& writenString, const char writeOverChar);
    void InsertString(const string& str, const int x, const int y);
    void Clear() { chars.clear(); }
};