// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CustomHook.h"

#include <iostream>
#include <windows.h>
#include <Winuser.h>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::string;


int main()
{ 
    auto hook = CustomHook();
    hook.SetHook();

    auto conf = confs_from_json("settings.json");
    remapper.init_from_conf(conf);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}