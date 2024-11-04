#include <fcntl.h>
#include <io.h>
#include "Console.h"
#include "Board.h"


int Console::_screenIndex = 0;
HANDLE Console::_screenHandle[2];


Console::Console()
{
    
}


Console::~Console()
{
    this->ScreenRelease();
}


void Console::ScreenInitialization()
{
    system("mode con cols=60 lines=40 | title Pacman");

    _screenHandle[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    _screenHandle[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    CONSOLE_CURSOR_INFO consoleCursorInfo;
    consoleCursorInfo.dwSize = 1;
    consoleCursorInfo.bVisible = FALSE;

    SetConsoleCursorInfo(_screenHandle[0], &consoleCursorInfo);
    SetConsoleCursorInfo(_screenHandle[1], &consoleCursorInfo);
}


void Console::ScreenFlipping()
{
    SetConsoleActiveScreenBuffer(_screenHandle[_screenIndex]);
    _screenIndex = (_screenIndex ? 0 : 1);
}

void Console::ScreenClear(int screenWidth, int screenHeight)
{
    DWORD dw;
    COORD Coor = { 0,0 };

    int screenSize = (screenWidth * 2) * screenHeight;

    FillConsoleOutputCharacter(_screenHandle[_screenIndex], ' ', screenSize, Coor, &dw);
}

void Console::ScreenRelease()
{
    CloseHandle(_screenHandle[0]);
    CloseHandle(_screenHandle[1]);
}

void Console::ScreenPrint(int x, int y, const char* string)
{
    COORD cursorPos = { cursorPos.X = x * 2 + 2,cursorPos.Y = y + 1 };

    SetConsoleCursorPosition(_screenHandle[_screenIndex], cursorPos);
    WriteFile(_screenHandle[_screenIndex], string, strlen(string), NULL, NULL);
}

void Console::ScreenColor(int color)
{
    color %= 16;
    SetConsoleTextAttribute(_screenHandle[_screenIndex], color);
}
