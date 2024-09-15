#include "Frame.h"


unsigned int Frame::GetSizeX() const
{
    if (chars.size() == 0)
        return 0;

    return chars[0].size();
}

void Frame::ResizeX(const unsigned int size)
{
    for (int y = 0; y < chars.size(); ++y)
        chars[y].resize(size);
}

void Frame::ReadFrameFromFile(const string& fileName, const int screenSizeX, const int screenSizeY)
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
            unsigned char c = file.get();

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

void Frame::ReplaceChar(const string& writenString, const unsigned char writeOverChar)
{
    for (int y = 0; y < GetSizeY(); ++y)
    {
        for (int x = 0; x < GetSizeX(); ++x)
        {
            unsigned char c = chars[y][x];

            // insert score message
            if (c == writeOverChar)
            {
                InsertString(writenString, x, y);
                x += writenString.size() - 1;
            }
        }
    }
}

void Frame::InsertString(const string& str, const int x, const int y)
{
    assert(y >= 0 && y < GetSizeY());
    assert(x >= 0 && x < GetSizeX());

    for (int i = 0; i < str.size(); ++i)
        chars[y][x + i] = str[i];
}