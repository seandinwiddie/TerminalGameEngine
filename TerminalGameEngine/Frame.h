#pragma once
#include "Config.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <cassert>
#include <string>

using string = std::string;
template<typename T> using vector = std::vector<T>;

class Frame
{
public:
    vector<vector<char>> chars;
    vector<vector<int>> colors;

public:
    size_t GetSizeY() const { return chars.size(); }
    size_t GetSizeX() const;
    void ResizeY(size_t size) { chars.resize(size); colors.resize(size); }
    void ResizeX(size_t size);
    void ReadFromFile(const string& fileName, size_t screenSizeX, size_t screenSizeY);
    void ReplaceChar(const string& writenString, char writeOverChar);
    void InsertString(const string& str, size_t xPos, size_t yPos);
    void Clear() { chars.clear(); }
    bool IsSetup(){ return GetSizeY() > 0; }
};