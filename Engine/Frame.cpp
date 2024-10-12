#include "Frame.h"
#include "StringUtils.h"
#include <cassert>


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

        if (y == 0)
            chars.SetWidth(line.size());

        assert(line.size() == chars.GetSizeX());

        chars.IncreaseSizeY();
        for (int x = 0; x < line.length(); ++x)
            chars.Set(line[x], x, y);

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
    for (size_t y = 0; y < GetSizeY(); ++y)
    {
        for (size_t x = 0; x < GetSizeX(); ++x)
        {
            char c = chars.Get(x,y);

            // insert score message
            if (c == writeOverChar)
            {
                for (int insertIt = 0; insertIt < writenString.size(); ++insertIt)
                    chars.Set(writenString[insertIt], x+insertIt, y);
                x += writenString.size() - 1;
            }
        }
    }
}

