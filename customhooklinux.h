#ifndef CUSTOMHOOKLINUX_H
#define CUSTOMHOOKLINUX_H
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <string.h>
#include <stdio.h>
#include <X11/XKBlib.h>
#include <iostream>

#include "keymap.h"



void emit(int fd, int type, int code, int val);

static const char *const evval[3] = {
    "RELEASED",
    "PRESSED ",
    "REPEATED"
};

inline void remap (const std::string & original, const std::string & remapped)
{
    custom_keymap[std_keymap[original]] = std_keymap[remapped];
}

void send_new_event(int fdo, int code)
{
    if (code != custom_keymap[code])
    {
        std::cout << "from: " << code << " to: " << custom_keymap[code] << std::endl;
        // sleep(1);
        emit(fdo, EV_KEY, KEY_BACKSPACE, 1);
        emit(fdo, EV_SYN, SYN_REPORT, 0);
        emit(fdo, EV_KEY, KEY_BACKSPACE, 0);
        emit(fdo, EV_SYN, SYN_REPORT, 0);
        // sleep(1);
        emit(fdo, EV_KEY, custom_keymap[code], 1);
        emit(fdo, EV_SYN, SYN_REPORT, 0);
        emit(fdo, EV_KEY, custom_keymap[code], 0);
        emit(fdo, EV_SYN, SYN_REPORT, 0);
        // sleep(1);
    }
    else
    {
        std::cout << "from: " << code << " to: " << code << std::endl;
        emit(fdo, EV_KEY, code, 1);
        emit(fdo, EV_SYN, SYN_REPORT, 0);
        emit(fdo, EV_KEY, code, 0);
        emit(fdo, EV_SYN, SYN_REPORT, 0);
    }
}

void init_custom_keymap()
{
    for (auto & p : std_keymap)
        custom_keymap[p.second] = p.second;
}
#endif // CUSTOMHOOKLINUX_H
