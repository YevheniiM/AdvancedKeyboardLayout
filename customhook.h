#ifndef CUSTOMHOOK_H
#define CUSTOMHOOK_H

#include <iostream>
#include <windows.h>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <string>
#include <map>

#include "mainwindow.h"

using std::string;

class VirtualKeyMapper
{
    std::map<string, int> key_codes;
    std::map<int, int> remapped_key_codes;

public:
    VirtualKeyMapper();

    std::map<string, int> get_original_key_codes();

    std::map<int, int> get_remapped_key_codes();

    void remap(string original, string remapped);

private:
    void initialize_key_codes();
};

class CustomHook
{
    int choice{};
public:
    CustomHook();

    CustomHook(int choice);

    void SetHook();

    void ReleaseHook();
};

#endif // CUSTOMHOOK_H
