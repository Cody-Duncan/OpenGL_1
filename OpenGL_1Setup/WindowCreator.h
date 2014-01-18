#pragma once

#include <Windows.h>

extern HWND ghMainWnd;
extern HINSTANCE ghInstance;
extern bool QuitMsgRecieved;

bool GenerateWindow(int ScreenWidth, int ScreenHeight);
void ActivateWindow();
void CheckMessagePump();