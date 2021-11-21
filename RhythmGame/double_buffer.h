#pragma once
#include <Windows.h>
#include <iostream>
#include <ctime>
void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();
void ScreenPrint(int x, int y, char* string);