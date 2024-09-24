#include "Frame.h"

size_t Frame::GetSizeX() const
{
    if (chars.size() == 0)
        return 0;

    return chars[0].size();
}

void Frame::ResizeX(size_t size)
{
    for (int y = 0; y < GetSizeY(); ++y)
    {
        chars[y].resize(size);
        colors[y].resize(size);
    }
}

void Frame::ReadFromFile(const string& fileName, size_t screenSizeX, size_t screenSizeY)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file)
    {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    ResizeY(screenSizeY);
    ResizeX(screenSizeX);

    //Read the data into the vector
    for (int y = 0; y < screenSizeY; ++y)
    {
        for (int x = 0; x < screenSizeX; ++x)
        {
            char c = file.get();

            //ignore invisible characters
            if (c == '\n' || c == '\r' || c == '\t' || c == '\0')
            {
                --x;
                continue;
            }
            chars[y][x] = c;
        }
    }

    std::reverse(chars.begin(), chars.end());
    return;
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