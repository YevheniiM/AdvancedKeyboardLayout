#pragma once
#include <iostream>
#include <windows.h>
#include <Winuser.h>
#include <Windows.h>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <string>
#include <map>
#include <chrono>
#include <thread>
#include "VirtualKeyMapper.h"


WindowsProperties properties;
HWND current;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//PostQuitMessage(0);
		break;
	case WM_TIMER:
	{
		DestroyWindow(hwnd);
		return 0;
	}
	case WM_CREATE:
	{
		for (int i = 0; i < properties.length; ++i)
		{
			int x = 0;

			if (i == 0)
				x = 5;
			else
				x = 5 + 5 * i + properties.width * i;

			std::string s = properties.key.remapped_to_str[i];
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();

			auto flags = WS_VISIBLE | WS_CHILD | BS_TEXT;
			std::cout << i << " " << properties.key.current << std::endl;
			if (i != properties.key.current)
				CreateWindow(TEXT("button"), stemp.c_str(),
					WS_VISIBLE | WS_CHILD | BS_TEXT | WS_DISABLED,
					x, 20, properties.width, properties.width,
					hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			else
				CreateWindow(TEXT("button"), stemp.c_str(),
					WS_VISIBLE | WS_CHILD | BS_TEXT,
					x, 20, properties.width, properties.width,
					hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		}

		if (current)
		{
			DestroyWindow(current);
		}

		current = hwnd;

		SetTimer(hwnd, NULL, 300, NULL);
		break;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
	}
	return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND show_popup()
{
	TCHAR title[] = TEXT("");
	HWND window = nullptr;

	TCHAR myclass[] = TEXT("myclass");
	WNDCLASSEX wndclass = {
		sizeof(WNDCLASSEX),
		CS_DBLCLKS,
		WindowProc,
		0,
		0,
		GetModuleHandle(0),
		LoadIcon(0, IDI_APPLICATION),
		LoadCursor(0,IDC_ARROW),
		HBRUSH(COLOR_WINDOW + 1),
		0,
		myclass,
		LoadIcon(0,IDI_APPLICATION)
	};

	RegisterClassEx(&wndclass);

	POINT cursorPos;
	GetCursorPos(&cursorPos);
	float x = cursorPos.x;
	float y = cursorPos.y;

	window = CreateWindow(
		myclass,
		title,
		WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_EX_TOOLWINDOW,
		x,
		y,
		(properties.length) * properties.width + 10 * properties.length + 5, //ШИРИНА!!!
		70, //ВЫСОТА
		(HWND)NULL,
		(HMENU)NULL,
		(HINSTANCE)NULL,
		NULL
	);

	std::cout << "creating" << std::endl;
	if (window)
		return window;
	else
		std::cout << "error creating window" << std::endl;

	return window;
}