#ifndef KEYMAP_H
#define KEYMAP_H

#include <QString>
#include <QToolButton>

class Keymap
{
public:
    bool is_multiple;
    QString activeButton;
    QString mode;
    double conf_value;
    std::map<std::string, std::vector<std::string>> changed_vector_of_buttons;
    std::map<QString, std::tuple<QToolButton*, int, int>> all_buttons;
    std::vector<std::pair<std::vector<std::string>, std::vector<std::string>>> shortcuts;

    Keymap();

    bool search(QString string);
};

#endif // KEYMAP_H
