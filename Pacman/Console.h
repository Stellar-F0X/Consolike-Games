#pragma once
#include <Windows.h>

class Console
{
public:
    Console();
    virtual ~Console();

public:
    static void ScreenInitialization();
    static void ScreenFlipping();
    static void ScreenRelease();
    static void ScreenClear(int width, int height);
    static void ScreenPrint(int x, int y, const char* string);
    static void ScreenColor(int color);

private:
    static int _screenIndex;
    static HANDLE _screenHandle[2];
};