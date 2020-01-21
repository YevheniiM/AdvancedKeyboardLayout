#ifndef ALL_BUTTONS_H
#define ALL_BUTTONS_H

#include <QString>
#include <QVector>

const QVector<QVector<QString>> buttons{
    {"First row", "esc", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "f11", "f12", "pause\nbreak", "prt sc\nsysrq", "delete\ninsert", ""},
    {"Second row", "`", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "-", "=", "backspace", "home"},
    {"Third row", "tab", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\\", "pgup"},
    {"Fourth row", "caps lock", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "enter", "pgdn"},
    {"Fifth row", "shift", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "right shift", "up", "end"},
    {"Sixth row", "ctrl", "fn", "win", "alt", "space", "right alt", "context\nmenu", "right ctrl", "left", "down", "right"}
};

#endif // ALL_BUTTONS_H
