#pragma once

#include <iostream>
#include <windows.h>
#include <Winuser.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <string>
#include <map>
#include <numeric>
#include <chrono>
#include <algorithm>
#include <thread>

#include "VirtualKeyMapper.h"
#include "CustomWindows.h"
#include "ProcessExe.h"

using std::string;


HHOOK hook;
KBDLLHOOKSTRUCT kbdStruct;
int extra = 234214;
extern VirtualKeyMapper remapper;
bool showing = false;

int back_space_vk = VK_BACK;
int back_space_sc = MapVirtualKeyA(back_space_vk, MAPVK_VK_TO_CHAR);

HWND wnd = NULL;

class TextProcessing
{
public:
	std::string sentence_buffer{};
	std::vector<std::string> tokens;
	std::vector<string> words_and_punkts{};
	string prog = "D:\\untitled2\\dist\\hello.exe";

	void produce_separated_tockens()
	{
		std::cout << "!!!!!!! " << sentence_buffer << std::endl;
		std::cout << "!!!!!!! " << sentence_buffer.size() << std::endl;

		string current;
		string token;

		for (char c : sentence_buffer)
		{
			if (!isspace(c) && iscntrl(c))
			{
				std::cout << "backspace" << std::endl;
				sentence_buffer.pop_back();
				continue;
			}

			if (std::iscntrl(c) || std::ispunct(c) || std::isspace(c))
			{
				if (current == "word")
				{
					words_and_punkts.push_back(token);
					token = "";
				}
				current = "punkt";
				token += c;
			}
			else
			{
				if (current == "punkt")
				{
					words_and_punkts.push_back(token);
					token = "";
				}
				current = "word";
				token += c;
			}
		}
		std::cout << "size: " << words_and_punkts.size() << std::endl;
	}

	void produce_clean_tokens()
	{
		std::stringstream iss(sentence_buffer);
		std::string word;

		while (iss >> word)
		{
			string result;
			std::remove_copy_if(word.begin(), word.end(),
				std::back_inserter(result),           
				[](int c) {return std::ispunct(c); }
			);
			tokens.push_back(result);
		}		
	}

	std::string send_to_danylo()
	{
		produce_clean_tokens();
		produce_separated_tockens();

		string s = std::accumulate(std::begin(tokens), std::end(tokens), string(),
			[](string& ss, string& s) {
			return ss.empty() ? s : ss + " " + s;
		});

		s = '"' + s + '"';
		auto processed = read_exe(prog, s);

		return processed;
	}

	string form_string_with_punkt()
	{
		string clean_sentence = send_to_danylo();

		std::cout << "" << std::endl;

		std::istringstream iss(clean_sentence);
		std::vector<std::string> results(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());


		if (results.size() != tokens.size())
		{
			std::cout << "!!! something went wrong" << std::endl;
			return sentence_buffer;
		}

		string final_{};
		for (int i = 0, j = 0; i < words_and_punkts.size(); ++i)
		{
			if (std::iscntrl(words_and_punkts[i][0]) || std::ispunct(words_and_punkts[i][0]) || std::isspace(words_and_punkts[i][0]))
			{
				final_ += words_and_punkts[i];
			}
			else
			{
				final_ += results[j];
				++j;
			}
		}

		std::cout << "final: " << final_ << std::endl;

		return final_;
	}

	void reset()
	{
		sentence_buffer = "";
		tokens = {};
		words_and_punkts = {};
	}

	bool append_new_char(string c)
	{
		sentence_buffer += c;
		return c == "." || c == "1" || c == "7";
	}
};

TextProcessing processor;


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
				if (wnd)
					DestroyWindow(wnd);
			}
			else if (wParam == WM_KEYDOWN && kbdStruct.dwExtraInfo == extra)
			{
				int i = 0;
				WCHAR keybuff[256] = { 0 };
				PBYTE keyState[256] = { 0 };
				HKL keyboardlayout = GetKeyboardLayout(0);
				GetKeyboardState((PBYTE)&keyState);

				i = ToUnicodeEx(kbdStruct.vkCode, kbdStruct.scanCode, (PBYTE)&keyState, (LPWSTR)&keybuff, sizeof(keybuff) / 16, 0, keyboardlayout);

				std::wstring ws(keybuff);
				string str(ws.begin(), ws.end());

				bool is_end = processor.append_new_char(str);
				if (is_end)
				{
					auto s = processor.form_string_with_punkt();
					int size = processor.sentence_buffer.size();
					std::cout << "SIZE: " << processor.sentence_buffer.size() << std::endl;

					for (int i = 0; i < size; ++i)
					{
						keybd_event(back_space_vk, back_space_sc, KEYEVENTF_EXTENDEDKEY | 0, 1111);
						std::this_thread::sleep_for(std::chrono::milliseconds(15));
					}
						
					for (char c : s)
					{
						SHORT vk = VkKeyScanExA(c, keyboardlayout);
						int sc = MapVirtualKeyA(vk, MAPVK_VK_TO_CHAR);
						keybd_event(vk, sc, KEYEVENTF_EXTENDEDKEY | 0, 1111);
						std::this_thread::sleep_for(std::chrono::milliseconds(15));
					}

					processor.reset();
				}
			}
			else if (wParam == WM_KEYUP && kbdStruct.dwExtraInfo == extra)
			{

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