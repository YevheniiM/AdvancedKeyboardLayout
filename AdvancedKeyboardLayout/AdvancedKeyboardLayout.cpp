// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include "winuser.h";
#include <windows.h>
#include <Winuser.h>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include "CustomHook.h"


using std::cout;
using std::cin;
using std::endl;
using std::string;

VirtualKeyMapper remapper;

char to_remap;

int main()
{
	auto hook = CustomHook();
	hook.SetHook();
	remapper.remap("A", "B");

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{

	}

	return 0;
}