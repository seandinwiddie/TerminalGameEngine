#pragma once
#include "Config.h"
#include "Vector2D.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <cassert>
#include <string>

using string = std::string;

class Frame
{
public:
    Vector2D<char> chars;

public:
    size_t GetSizeY() const { return chars.GetSizeY(); }
    size_t GetSizeX() const { return chars.GetSizeX(); }

    void ReadFromFile(const string& fileName);
    void ReplaceChar(const string& writenString, char writeOverChar);
    bool IsSetup(){ return GetSizeY() > 0; }

    void RemoveNotAllowedChars(string& str);
};