#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <fstream>

#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/istreamwrapper.h"

using rapidjson::Document;
using RemapperConf = struct RemapperConf
{
    enum RemapMode
    {
        LONG_PRESS, MULTIPLE_PRESS
    };

    std::map<std::string, RemapMode> remap_mode_str2enum{
            {"long_press",     LONG_PRESS},
            {"LongPress",      LONG_PRESS},
            {"multiple_press", MULTIPLE_PRESS},
            {"MultiplePress",  MULTIPLE_PRESS},
    };

    int remapper_pid{};
    std::map<std::string, std::vector<std::string>> keymap{};
    RemapMode mode{LONG_PRESS};
    int remap_conf_value{};

    RemapperConf() = default;


    RemapperConf(const Document &d) :
            remapper_pid{d["id"].GetInt()},
            mode{remap_mode_str2enum[d["mode"].GetObject()["type"].GetString()]},
            remap_conf_value{d["mode"].GetObject()["value"].GetInt()}
    {
        for (auto doc_it = d["keymap"].MemberBegin(); doc_it != d["keymap"].MemberEnd(); ++doc_it)
            keymap[doc_it->name.GetString()] = array2vector(doc_it);
    }


    std::vector<std::string> array2vector(const rapidjson::Document::ConstMemberIterator &doc_it)
    {
//          rapidjson::Array to std::vector
        std::vector<std::string> remaps{};
        auto remaps_array = doc_it->value.GetArray();
        remaps.reserve(remaps_array.Size());
        for (auto i = 0; i < remaps_array.Size(); ++i)
            remaps.emplace_back(remaps_array[i].GetString());
        return remaps;
    }
};


RemapperConf confs_from_json(const std::string &json_file_name);

void write_to_json(const std::string &json_file_name, int id, std::string mode, double conf_value, std::map<std::string, std::vector<std::string>> keys);

#endif // JSON_MANAGER_H
