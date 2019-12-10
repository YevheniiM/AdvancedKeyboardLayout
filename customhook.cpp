#include "customhook.h"

HHOOK hook;
KBDLLHOOKSTRUCT kbdStruct;
int extra = 234214;
extern VirtualKeyMapper remapper;

LRESULT CALLBACK ShowKeys(int code, WPARAM wParam, LPARAM lParam)
{
    if (code >= 0)
    {
        WCHAR name[128];
        UINT scanCode = MapVirtualKeyW(kbdStruct.vkCode, MAPVK_VK_TO_VSC);
        LONG lParamValue = (scanCode << 16);
        int result = GetKeyNameTextW(lParamValue, name, 128);
        kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

        if (result > 0)
        {
            if (wParam == WM_KEYDOWN)
            {
                std::wcout << name << " pressed down (" << kbdStruct.vkCode << ") in " << kbdStruct.time << std::endl;
            }
            else if (wParam == WM_KEYUP)
            {
                std::wcout << name << " pressed (" << kbdStruct.vkCode << ") in " << kbdStruct.time << std::endl;
            }
        }
    }
    return CallNextHookEx(hook, code, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
    if (code >= 0)
    {
        WCHAR name[128];
        UINT scanCode = MapVirtualKeyW(kbdStruct.vkCode, MAPVK_VK_TO_VSC);
        LONG lParamValue = (scanCode << 16);
        int result = GetKeyNameTextW(lParamValue, name, 128);
        kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

        //auto remapped_virtual_key = VkKeyScanA(to_remap) & 0xff;
        //auto remapped_scan_code = MapVirtualKeyA(remapped_virtual_key, MAPVK_VK_TO_CHAR);

        int remapped_virtual_key = (int)kbdStruct.vkCode;
        int remapped_scan_code;

        if (result > 0)
        {
            for (auto i : remapper.get_remapped_key_codes())
            {
                if (wParam == WM_KEYDOWN && kbdStruct.dwExtraInfo == extra)
                {
                    std::wcout << i.first << " | " << (int)kbdStruct.vkCode << std::endl;
                }

                if (i.first == (int)kbdStruct.vkCode)
                {
                    remapped_virtual_key = i.second;
                }
            }

            remapped_scan_code = MapVirtualKeyA(remapped_virtual_key, MAPVK_VK_TO_CHAR);

            if (wParam == WM_KEYDOWN && kbdStruct.dwExtraInfo != extra)
            {
                keybd_event(remapped_virtual_key, remapped_scan_code, KEYEVENTF_EXTENDEDKEY | 0, extra);
                return 1;
            }
            else if (wParam == WM_KEYUP && kbdStruct.dwExtraInfo != extra)
            {
                keybd_event(remapped_virtual_key, remapped_scan_code, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, extra);
                return 1;
            }
            else if (wParam == WM_KEYDOWN && kbdStruct.dwExtraInfo == extra)
            {

            }
            else if (wParam == WM_KEYUP && kbdStruct.dwExtraInfo == extra)
            {

            }
        }

    }
    return CallNextHookEx(hook, code, wParam, lParam);
}


CustomHook::CustomHook()
{
    choice = 2;
}

CustomHook::CustomHook(int choice)
{
    this->choice = choice;
}

void CustomHook::SetHook()
{
    bool is_set = false;

    if (choice == 1)
    {
        if ((hook = SetWindowsHookEx(WH_KEYBOARD_LL, ShowKeys, nullptr, 0)))
        {
            is_set = true;
        }
    }
    else if (choice == 2)
    {
        if ((hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, nullptr, 0)))
        {
            is_set = true;
        }
    }

    if (!is_set)
    {
        MessageBoxA(nullptr, "Failed to install hook!", "Error", MB_ICONERROR);
    }
    else
    {
        MessageBoxA(nullptr, "Hook installed", "Success", MB_OK);
    }
}

void CustomHook::ReleaseHook()
{
    UnhookWindowsHookEx(hook);
    MessageBoxA(nullptr, "Hook deleted", "Success", MB_OK);
}

VirtualKeyMapper::VirtualKeyMapper()
{
    initialize_key_codes();
}

std::map<std::string, int> VirtualKeyMapper::get_original_key_codes()
{
    return key_codes;
}

std::map<int, int> VirtualKeyMapper::get_remapped_key_codes()
{
    return remapped_key_codes;
}

void VirtualKeyMapper::remap(std::string original, std::string remapped)
{
    remapped_key_codes[key_codes[original]] = key_codes[remapped];
}

void VirtualKeyMapper::initialize_key_codes()
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
}
