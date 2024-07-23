#pragma once
#include <iostream>
#include <Windows.h>
#include <stdint.h>


#define turnOnPointer true
#define turnOffPointer false
#define ll long long
#define ull unsigned long long


using int4 = int32_t;

void GotoXY(short x, short y);

void showPointer(bool action);

void cls();

void clrscr(COORD start, COORD end);

void setColor(int backgroundColor, int textColor);

void SetScreenBufferSize(int width, int height);

void setConsoleSize(int width, int height);

void setWindowBufferSize(int height, int width);