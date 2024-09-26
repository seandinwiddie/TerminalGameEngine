#include "UIPrinter.h"

UIPrinter::UIPrinter(size_t screenSizeX, size_t screenSizeY, size_t screenPadding, int marginsColor) : 
    Printer(screenSizeX, screenSizeY, screenPadding)
{
    DrawMargins(marginsColor);
};

void UIPrinter::PrintOnHeader(const string& header, int xPos, int color)
{
    terminal.SetColor(color);
    terminal.SetCursorPosition(xPos, 0);
    terminal.Cout(header);
}

void UIPrinter::PrintGameOverWindow(const Frame& window, int color)
{
    if (window.GetSizeY() == 0)
        return;

    Terminal::Instance().SetColor(color);
    for (size_t y = 0; y < screenSizeY; ++y)
    {
        for (size_t x = 0; x < screenSizeX; ++x)
        {
            char c = window.chars[y][x];
            if (c != GAME_OVER_FRAME_IGNORED_CHAR)
            {
                terminal.SetCursorPosition(x + MARGIN_OFFSET_X, GetMaxTerminalY() - y - MARGIN_OFFSET_BOTTOM_Y);
                terminal.Cout(c);
            }
        }
    }
}

void UIPrinter::DrawMargins(int color)
{
    terminal.SetColor(color);

    //horizontal
    terminal.SetCursorPosition(0, 1);
    DrawHorizontalMargin();
    terminal.SetCursorPosition(0, static_cast<int>(GetMaxTerminalY()));
    DrawHorizontalMargin();

    //vertical
    for (size_t y = MARGIN_OFFSET_TOP_Y; y < GetMaxTerminalY(); ++y)
    {
        terminal.SetCursorPosition(size_t(0), y);
        terminal.Cout(MARGIN_VERTICAL_CHAR);
        terminal.SetCursorPosition(GetMaxTerminalX(), y);
        terminal.Cout(MARGIN_VERTICAL_CHAR);
    }
}

void UIPrinter::DrawHorizontalMargin()
{
    string line = "";
    for (int x = 0; x < screenSizeX + 2; ++x)
        line += MARGIN_HORIZONTAL_CHAR;
    terminal.Cout(line);
}


