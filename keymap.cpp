#include "keymap.h"

Keymap::Keymap()
{

}

bool Keymap::search(QString text)
{
    return all_buttons.find(text) == all_buttons.end();
}
