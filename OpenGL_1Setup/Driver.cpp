#include <string>       //string
#include <stdio.h>      //cout, endl
#include <windows.h>    //windows header
#include <fstream>      //file stream
#include <limits>       //numeric limits
#include <crtdbg.h>     //memory leak debugging

#include "WindowCreator.h"

int ScreenWidth = 800;
int ScreenHeight = 600;

int main()
{
    GenerateWindow(ScreenWidth, ScreenHeight);
    ActivateWindow();

    return 0;
}