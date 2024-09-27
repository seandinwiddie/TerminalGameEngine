#include "Frame.h"
#include "StringUtils.h"
#include <cassert>

size_t Frame::GetSizeX() const
{
    if (chars.size() == 0)
        return 0;

    return chars[0].size();
}

void Frame::ReadFromFile(const string& fileName)
{
    if(fileName == "")
        return;

    std::ifstream file(fileName, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error opening frame file: " << fileName << std::endl;
        return;
    }

    string line = "";
    int y = 0;
    //Read data into the vector
    while(std::getline(file, line))
    {
        RemoveNotAllowedChars(line);

        chars.resize(y+1);
        chars[y].resize(line.length());

        for (int x = 0; x < line.length(); ++x)
            chars[y][x] = line[x];

        assert(line.size() == chars[0].size());

        line = "";
        ++y;
    }

    return;
}

void Frame::RemoveNotAllowedChars(string& str)
{
    StringUtils::RemoveInstancesOfChar(str, '\n');
    StringUtils::RemoveInstancesOfChar(str, '\r');
    StringUtils::RemoveInstancesOfChar(str, '\t');
    StringUtils::RemoveInstancesOfChar(str, '\0');
}

void Frame::ReplaceChar(const string& writenString, char writeOverChar)
{
    for (int y = 0; y < GetSizeY(); ++y)
    {
        for (int x = 0; x < GetSizeX(); ++x)
        {
            char c = chars[y][x];

            // insert score message
            if (c == writeOverChar)
            {
                InsertString(writenString, x, y);
                x += static_cast<int>(writenString.size()) - 1;
            }
        }
    }
}

void Frame::InsertString(const string& str, size_t x, size_t y)
{
    assert(y < GetSizeY());
    assert(x < GetSizeX());

    for (int i = 0; i < str.size(); ++i)
        chars[y][x + i] = str[i];
}

