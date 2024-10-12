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

public:
    size_t GetSizeY() const { return chars.size(); }
    size_t GetSizeX() const;
    void SetEmpty() { chars.resize(0); }

    void ReadFromFile(const string& fileName);
    void ReplaceChar(const string& writenString, char writeOverChar);
    void InsertString(const string& str, size_t xPos, size_t yPos);
    void Clear() { chars.clear(); }
    bool IsSetup(){ return GetSizeY() > 0; }



    void RemoveNotAllowedChars(string& str);
};