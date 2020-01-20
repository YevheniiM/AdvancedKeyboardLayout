#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>
#include <tchar.h>

#include "RemapperConf.h"

using std::string;

struct RemmapedKey
{
	std::vector<int> remapped_to_int{};
	std::vector<string> remapped_to_str{};
	int current = 0;
	int mode;
	unsigned long time;
	unsigned long triggered_time;
	float duration_between_presses;
	bool remove_prev = true;

	void set_triggered_time(unsigned long t_time)
	{
		duration_between_presses = (t_time - triggered_time) / 1000.0;
		triggered_time = t_time;
		std::cout << duration_between_presses << std::endl << std::endl << std::endl;
	}

	void incr_current()
	{
		if (duration_between_presses < time)
		{
			std::cout << "current " << current << std::endl;
			++current;
			current = (current % remapped_to_int.size());
			remove_prev = true;
		}
		else
		{
			std::cout << "current + " << current << std::endl;
			current = 0;
			remove_prev = false;
		}
	}
};

struct WindowsProperties
{
	RemmapedKey key;
	int width = 0;
	int length = 0;
};

class VirtualKeyMapper
{
	std::map<std::string, std::string> high_level_map;
	std::map<std::string, int> key_codes;
	std::map<int, RemmapedKey> remapped_key_codes;

public:
	VirtualKeyMapper()
	{
		initialize_key_codes();
	}

	std::map<string, int> get_original_key_codes()
	{
		return key_codes;
	}

	std::map<int, RemmapedKey>& get_remapped_key_codes()
	{
		return remapped_key_codes;
	}

	void init_from_conf(RemapperConf conf)
	{
		for (auto i : conf.keymap)
			for (string j : i.second)
			{
				std::cout << i.first << " " << j << std::endl;

				string low_original = "";
				string low_remapped = "";

				try
				{
					low_original = high_level_map[i.first];
					low_remapped = high_level_map[j];
				}
				catch (...) {}

				if (low_original != "" && low_remapped != "")
					if (!std::count(remapped_key_codes[key_codes[low_original]].remapped_to_int.begin(), remapped_key_codes[key_codes[low_original]].remapped_to_int.end(), key_codes[low_remapped]))
					{
						remapped_key_codes[key_codes[low_original]].remapped_to_int.push_back(key_codes[low_remapped]);
						remapped_key_codes[key_codes[low_original]].remapped_to_str.push_back(j);
					}
					else
						std::wcout << "The proper key was not found" << std::endl;

				remapped_key_codes[key_codes[low_original]].current = 0;
				remapped_key_codes[key_codes[low_original]].mode = conf.mode;
				remapped_key_codes[key_codes[low_original]].time = conf.remap_conf_value;
			}
	}

private:
	void initialize_key_codes()
	{
		key_codes["VK_LBUTTON"] = VK_LBUTTON;
		key_codes["VK_RBUTTON"] = VK_RBUTTON;
		key_codes["VK_CANCEL"] = VK_CANCEL;
		key_codes["VK_MBUTTON"] = VK_MBUTTON;
		key_codes["VK_XBUTTON1"] = VK_XBUTTON1;
		key_codes["VK_XBUTTON2"] = VK_XBUTTON2;
		key_codes["VK_BACK"] = VK_BACK;
		key_codes["VK_TAB"] = VK_TAB;
		key_codes["VK_CLEAR"] = VK_CLEAR;
		key_codes["VK_RETURN"] = VK_RETURN;
		key_codes["VK_SHIFT"] = VK_SHIFT;
		key_codes["VK_CONTROL"] = VK_CONTROL;
		key_codes["VK_MENU"] = VK_MENU;
		key_codes["VK_PAUSE"] = VK_PAUSE;
		key_codes["VK_CAPITAL"] = VK_CAPITAL;
		key_codes["VK_KANA"] = VK_KANA;
		key_codes["VK_HANGUL"] = VK_HANGUL;
		key_codes["VK_JUNJA"] = VK_JUNJA;
		key_codes["VK_FINAL"] = VK_FINAL;
		key_codes["VK_HANJA"] = VK_HANJA;
		key_codes["VK_KANJI"] = VK_KANJI;
		key_codes["VK_ESCAPE"] = VK_ESCAPE;
		key_codes["VK_CONVERT"] = VK_CONVERT;
		key_codes["VK_NONCONVERT"] = VK_NONCONVERT;
		key_codes["VK_ACCEPT"] = VK_ACCEPT;
		key_codes["VK_MODECHANGE"] = VK_MODECHANGE;
		key_codes["VK_SPACE"] = VK_SPACE;
		key_codes["VK_PRIOR"] = VK_PRIOR;
		key_codes["VK_NEXT"] = VK_NEXT;
		key_codes["VK_END"] = VK_END;
		key_codes["VK_HOME"] = VK_HOME;
		key_codes["VK_LEFT"] = VK_LEFT;
		key_codes["VK_UP"] = VK_UP;
		key_codes["VK_RIGHT"] = VK_RIGHT;
		key_codes["VK_DOWN"] = VK_DOWN;
		key_codes["VK_SELECT"] = VK_SELECT;
		key_codes["VK_PRINT"] = VK_PRINT;
		key_codes["VK_EXECUTE"] = VK_EXECUTE;
		key_codes["VK_SNAPSHOT"] = VK_SNAPSHOT;
		key_codes["VK_INSERT"] = VK_INSERT;
		key_codes["VK_DELETE"] = VK_DELETE;
		key_codes["VK_HELP"] = VK_HELP;
		key_codes["VK_LWIN"] = VK_LWIN;
		key_codes["VK_RWIN"] = VK_RWIN;
		key_codes["VK_APPS"] = VK_APPS;
		key_codes["VK_SLEEP"] = VK_SLEEP;
		key_codes["VK_NUMPAD0"] = VK_NUMPAD0;
		key_codes["VK_NUMPAD1"] = VK_NUMPAD1;
		key_codes["VK_NUMPAD2"] = VK_NUMPAD2;
		key_codes["VK_NUMPAD3"] = VK_NUMPAD3;
		key_codes["VK_NUMPAD4"] = VK_NUMPAD4;
		key_codes["VK_NUMPAD5"] = VK_NUMPAD5;
		key_codes["VK_NUMPAD6"] = VK_NUMPAD6;
		key_codes["VK_NUMPAD7"] = VK_NUMPAD7;
		key_codes["VK_NUMPAD8"] = VK_NUMPAD8;
		key_codes["VK_NUMPAD9"] = VK_NUMPAD9;
		key_codes["VK_MULTIPLY"] = VK_MULTIPLY;
		key_codes["VK_ADD"] = VK_ADD;
		key_codes["VK_SEPARATOR"] = VK_SEPARATOR;
		key_codes["VK_SUBTRACT"] = VK_SUBTRACT;
		key_codes["VK_DECIMAL"] = VK_DECIMAL;
		key_codes["VK_DIVIDE"] = VK_DIVIDE;
		key_codes["VK_F1"] = VK_F1;
		key_codes["VK_F2"] = VK_F2;
		key_codes["VK_F3"] = VK_F3;
		key_codes["VK_F4"] = VK_F4;
		key_codes["VK_F5"] = VK_F5;
		key_codes["VK_F6"] = VK_F6;
		key_codes["VK_F7"] = VK_F7;
		key_codes["VK_F8"] = VK_F8;
		key_codes["VK_F9"] = VK_F9;
		key_codes["VK_F10"] = VK_F10;
		key_codes["VK_F11"] = VK_F11;
		key_codes["VK_F12"] = VK_F12;
		key_codes["VK_F13"] = VK_F13;
		key_codes["VK_F14"] = VK_F14;
		key_codes["VK_F15"] = VK_F15;
		key_codes["VK_F16"] = VK_F16;
		key_codes["VK_F17"] = VK_F17;
		key_codes["VK_F18"] = VK_F18;
		key_codes["VK_F19"] = VK_F19;
		key_codes["VK_F20"] = VK_F20;
		key_codes["VK_F21"] = VK_F21;
		key_codes["VK_F22"] = VK_F22;
		key_codes["VK_F23"] = VK_F23;
		key_codes["VK_F24"] = VK_F24;
		key_codes["VK_NUMLOCK"] = VK_NUMLOCK;
		key_codes["VK_SCROLL"] = VK_SCROLL;
		key_codes["VK_LSHIFT"] = VK_LSHIFT;
		key_codes["VK_RSHIFT"] = VK_RSHIFT;
		key_codes["VK_LCONTROL"] = VK_LCONTROL;
		key_codes["VK_RCONTROL"] = VK_RCONTROL;
		key_codes["VK_LMENU"] = VK_LMENU;
		key_codes["VK_RMENU"] = VK_RMENU;
		key_codes["VK_BROWSER_BACK"] = VK_BROWSER_BACK;
		key_codes["VK_BROWSER_FORWARD"] = VK_BROWSER_FORWARD;
		key_codes["VK_BROWSER_REFRESH"] = VK_BROWSER_REFRESH;
		key_codes["VK_BROWSER_STOP"] = VK_BROWSER_STOP;
		key_codes["VK_BROWSER_SEARCH"] = VK_BROWSER_SEARCH;
		key_codes["VK_BROWSER_FAVORITES"] = VK_BROWSER_FAVORITES;
		key_codes["VK_BROWSER_HOME"] = VK_BROWSER_HOME;
		key_codes["VK_VOLUME_MUTE"] = VK_VOLUME_MUTE;
		key_codes["VK_VOLUME_DOWN"] = VK_VOLUME_DOWN;
		key_codes["VK_VOLUME_UP"] = VK_VOLUME_UP;
		key_codes["VK_MEDIA_NEXT_TRACK"] = VK_MEDIA_NEXT_TRACK;
		key_codes["VK_MEDIA_PREV_TRACK"] = VK_MEDIA_PREV_TRACK;
		key_codes["VK_MEDIA_STOP"] = VK_MEDIA_STOP;
		key_codes["VK_MEDIA_PLAY_PAUSE"] = VK_MEDIA_PLAY_PAUSE;
		key_codes["VK_LAUNCH_MAIL"] = VK_LAUNCH_MAIL;
		key_codes["VK_LAUNCH_MEDIA_SELECT"] = VK_LAUNCH_MEDIA_SELECT;
		key_codes["VK_LAUNCH_APP1"] = VK_LAUNCH_APP1;
		key_codes["VK_LAUNCH_APP2"] = VK_LAUNCH_APP2;
		key_codes["VK_OEM_1"] = VK_OEM_1;
		key_codes["VK_OEM_PLUS"] = VK_OEM_PLUS;
		key_codes["VK_OEM_COMMA"] = VK_OEM_COMMA;
		key_codes["VK_OEM_MINUS"] = VK_OEM_MINUS;
		key_codes["VK_OEM_PERIOD"] = VK_OEM_PERIOD;
		key_codes["VK_OEM_2"] = VK_OEM_2;
		key_codes["VK_OEM_3"] = VK_OEM_3;
		key_codes["VK_OEM_4"] = VK_OEM_4;
		key_codes["VK_OEM_5"] = VK_OEM_5;
		key_codes["VK_OEM_6"] = VK_OEM_6;
		key_codes["VK_OEM_7"] = VK_OEM_7;
		key_codes["VK_OEM_8"] = VK_OEM_8;
		key_codes["VK_OEM_102"] = VK_OEM_102;
		key_codes["VK_PROCESSKEY"] = VK_PROCESSKEY;
		key_codes["VK_PACKET"] = VK_PACKET;
		key_codes["VK_ATTN"] = VK_ATTN;
		key_codes["VK_CRSEL"] = VK_CRSEL;
		key_codes["VK_EXSEL"] = VK_EXSEL;
		key_codes["VK_EREOF"] = VK_EREOF;
		key_codes["VK_PLAY"] = VK_PLAY;
		key_codes["VK_ZOOM"] = VK_ZOOM;
		key_codes["VK_NONAME"] = VK_NONAME;
		key_codes["VK_PA1"] = VK_PA1;
		key_codes["VK_OEM_CLEAR"] = VK_OEM_CLEAR;
		key_codes["0"] = 0x30;
		key_codes["1"] = 0x31;
		key_codes["2"] = 0x32;
		key_codes["3"] = 0x33;
		key_codes["4"] = 0x34;
		key_codes["5"] = 0x35;
		key_codes["6"] = 0x36;
		key_codes["7"] = 0x37;
		key_codes["8"] = 0x38;
		key_codes["9"] = 0x39;
		key_codes["A"] = 0x41;
		key_codes["B"] = 0x42;
		key_codes["C"] = 0x43;
		key_codes["D"] = 0x44;
		key_codes["E"] = 0x45;
		key_codes["F"] = 0x46;
		key_codes["G"] = 0x47;
		key_codes["H"] = 0x48;
		key_codes["I"] = 0x49;
		key_codes["J"] = 0x4A;
		key_codes["K"] = 0x4B;
		key_codes["L"] = 0x4C;
		key_codes["N"] = 0x4E;
		key_codes["O"] = 0x4F;
		key_codes["P"] = 0x50;
		key_codes["Q"] = 0x51;
		key_codes["R"] = 0x52;
		key_codes["S"] = 0x53;
		key_codes["T"] = 0x54;
		key_codes["U"] = 0x55;
		key_codes["V"] = 0x56;
		key_codes["W"] = 0x57;
		key_codes["X"] = 0x58;
		key_codes["Y"] = 0x59;
		key_codes["Z"] = 0x5A;

		high_level_map["esc"] = "VK_ESCAPE";
		high_level_map["f1"] = "VK_F1";
		high_level_map["f2"] = "VK_F2";
		high_level_map["f3"] = "VK_F3";
		high_level_map["f4"] = "VK_F4";
		high_level_map["f5"] = "VK_F5";
		high_level_map["f6"] = "VK_F6";
		high_level_map["f7"] = "VK_F7";
		high_level_map["f8"] = "VK_F8";
		high_level_map["f9"] = "VK_F9";
		high_level_map["f10"] = "VK_F10";
		high_level_map["f11"] = "VK_F11";
		high_level_map["f12"] = "VK_F12";
		high_level_map["pause/nbreak"] = "";
		high_level_map["prt sc/nsysrq"] = "VK_SNAPSHOT";
		high_level_map["delete/ninsert"] = "";
		high_level_map["home"] = "";
		high_level_map["pgup"] = "";
		high_level_map["pgdn"] = "";
		high_level_map["end"] = "";
		high_level_map["`"] = "";
		high_level_map["0"] = "0";
		high_level_map["1"] = "1";
		high_level_map["2"] = "2";
		high_level_map["3"] = "3";
		high_level_map["4"] = "4";
		high_level_map["5"] = "5";
		high_level_map["6"] = "6";
		high_level_map["7"] = "7";
		high_level_map["8"] = "8";
		high_level_map["9"] = "9";
		high_level_map["-"] = "";
		high_level_map["="] = "";
		high_level_map["backspace"] = "";
		high_level_map["num lk/scr lk"] = "";
		high_level_map["/"] = "";
		high_level_map["*"] = "";
		high_level_map["-"] = "";
		high_level_map["tab"] = "VK_TAB";
		high_level_map["q"] = "Q";
		high_level_map["w"] = "W";
		high_level_map["e"] = "E";
		high_level_map["r"] = "R";
		high_level_map["t"] = "T";
		high_level_map["u"] = "U";
		high_level_map["y"] = "Y";
		high_level_map["i"] = "I";
		high_level_map["o"] = "O";
		high_level_map["p"] = "P";
		high_level_map["["] = "";
		high_level_map["]"] = "";
		high_level_map["\\"] = "";
		high_level_map["caps lock"] = "";
		high_level_map["a"] = "A";
		high_level_map["s"] = "S";
		high_level_map["d"] = "D";
		high_level_map["f"] = "F";
		high_level_map["g"] = "G";
		high_level_map["h"] = "H";
		high_level_map["j"] = "J";
		high_level_map["k"] = "K";
		high_level_map["l"] = "L";
		high_level_map[";"] = "";
		high_level_map["enter"] = "";
		high_level_map["shift"] = "";
		high_level_map["z"] = "Z";
		high_level_map["x"] = "X";
		high_level_map["c"] = "C";
		high_level_map["v"] = "V";
		high_level_map["b"] = "B";
		high_level_map["n"] = "N";
		high_level_map["m"] = "M";
		high_level_map[","] = "";
		high_level_map["."] = "";
		high_level_map["/"] = "";
		high_level_map["right shift"] = "";
		high_level_map["up"] = "VK_UP";
		high_level_map["ctrl"] = "";
		high_level_map["fn"] = "";
		high_level_map["win"] = "";
		high_level_map["alt"] = "";
		high_level_map["space"] = "";
		high_level_map["right alt"] = "";
		high_level_map["context/nmenu"] = "";
		high_level_map["right ctrl"] = "";
		high_level_map["left"] = "VK_LEFT";
		high_level_map["down"] = "VK_DOWN";
		high_level_map["right"] = "VK_RIGHT";
	}
};

VirtualKeyMapper remapper;