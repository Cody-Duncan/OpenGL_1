#pragma once

#include <Windows.h>

extern HWND ghMainWnd;
extern HINSTANCE ghInstance;

bool GenerateWindow(int ScreenWidth, int ScreenHeight);
void ActivateWindow();