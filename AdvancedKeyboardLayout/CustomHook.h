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
#include <numeric>
#include <chrono>
#include <thread>

#include "VirtualKeyMapper.h"
#include "CustomWindows.h"

using std::string;


HHOOK hook;
KBDLLHOOKSTRUCT kbdStruct;
int extra = 234214;
extern VirtualKeyMapper remapper;
bool showing = false;

int back_space_vk = VK_BACK;
int back_space_sc = MapVirtualKeyA(back_space_vk, MAPVK_VK_TO_CHAR);

HWND wnd = NULL;


struct TextProcessing
{
	std::string sentence_buffer{};
	std::vector<std::string> tokens;

	std::string process_sentence()
	{
		
	}

	std::string send_to_danylo()
	{
		string s = std::accumulate(std::begin(tokens), std::end(tokens), string(),
			[](string& ss, string& s) {
			return ss.empty() ? s : ss + " " + s;
		});
		std::cout << s << std::endl;
	}

	bool append_new_char(char c)
	{
		sentence_buffer += c;
		return c == '.' || c == '!' || c == '?';
	}
};


LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code >= 0)
	{
		bool backspace = false;
		WCHAR name[128];
		UINT scanCode = MapVirtualKeyW(kbdStruct.vkCode, MAPVK_VK_TO_VSC);
		LONG lParamValue = (scanCode << 16);
		int result = GetKeyNameTextW(lParamValue, name, 128);
		kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

		int remapped_virtual_key = (int)kbdStruct.vkCode;
		int remapped_scan_code;

		if (result > 0)
		{
			for (auto& i : remapper.get_remapped_key_codes())
			{	
				if (wParam == WM_KEYDOWN && kbdStruct.dwExtraInfo == extra)
					std::wcout << i.first << " | " << (int)kbdStruct.vkCode << std::endl;

				if(wParam == WM_KEYDOWN && kbdStruct.dwExtraInfo != extra)
					if (i.first == (int)kbdStruct.vkCode)
					{
						properties.length = i.second.remapped_to_str.size();
						properties.width = 35;
						properties.key = i.second;

						remapped_virtual_key = i.second.remapped_to_int[i.second.current];
						i.second.set_triggered_time(kbdStruct.time);
						i.second.incr_current();
						backspace = i.second.remove_prev;

						wnd = show_popup();
					}
			}

			remapped_scan_code = MapVirtualKeyA(remapped_virtual_key, MAPVK_VK_TO_CHAR);

			if (wParam == WM_KEYDOWN && kbdStruct.dwExtraInfo != extra)
			{

				if (!backspace)
					keybd_event(remapped_virtual_key, remapped_scan_code, KEYEVENTF_EXTENDEDKEY | 0, extra);
				else
				{
					keybd_event(back_space_vk, back_space_sc, KEYEVENTF_EXTENDEDKEY | 0, extra);
					keybd_event(remapped_virtual_key, remapped_scan_code, KEYEVENTF_EXTENDEDKEY | 0, extra);
				}
				
				if (wnd)
					ShowWindow(wnd, SW_SHOWNOACTIVATE);
				
				return 1;
			}
			else if (wParam == WM_KEYUP && kbdStruct.dwExtraInfo != extra)
			{
				std::cout << "key up" << std::endl;
				if (wnd)
				{
					DestroyWindow(wnd);
					std::cout << "destroyed" << std::endl;
				}
			}
			else if (wParam == WM_KEYDOWN && kbdStruct.dwExtraInfo == extra)
			{

			}
			else if (wParam == WM_KEYUP && kbdStruct.dwExtraInfo == extra)
			{
				std::cout << "key up" << std::endl;
				if (wnd)
				{
					DestroyWindow(wnd);
					std::cout << "destroyed" << std::endl;
				}
					
			}
		}
	}
	return CallNextHookEx(hook, code, wParam, lParam);
}


class CustomHook
{
public:
	CustomHook()
	{
	}

	~CustomHook()
	{
		ReleaseHook();
	}

	void SetHook()
	{
		hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, nullptr, 0);
	}

	void ReleaseHook()
	{
		UnhookWindowsHookEx(hook);
	}
};