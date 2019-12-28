// #define _GNU_SOURCE

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

// #include "keymap.h"
#include "remapper.hpp"




int main(void)
{

    auto rmp = Remapper();
    // auto custom_keymap = std_keymap;
    rmp.remap("KEY_A", "KEY_H");
    rmp.remap("KEY_S", "KEY_E");
    rmp.remap("KEY_D", "KEY_L");
    rmp.remap("KEY_F", "KEY_L");
    rmp.remap("KEY_G", "KEY_O");
    rmp.remap("KEY_H", "KEY_COMMA");
    rmp.remap("KEY_J", "KEY_SPACE");
    rmp.remap("KEY_Z", "KEY_M");
    rmp.remap("KEY_X", "KEY_R");
    rmp.remap("KEY_C", "KEY_DOT");
    rmp.remap("KEY_V", "KEY_O");
    rmp.remap("KEY_B", "KEY_L");
    rmp.remap("KEY_N", "KEY_E");
    rmp.remap("KEY_M", "KEY_H");

    rmp.listen();

    return EXIT_FAILURE;
}