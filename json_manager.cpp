#include "json_manager.h"
#include <rapidjson/prettywriter.h>

using rapidjson::Value;
using rapidjson::PrettyWriter;
using rapidjson::Document;
using rapidjson::kObjectType;
using rapidjson::kStringType;
using rapidjson::StringBuffer;
using rapidjson::IStreamWrapper;

#include <iostream>
#include "keymap.h"

std::vector<std::string> array2vector(const rapidjson::Document::ConstMemberIterator &doc_it)
{
    std::vector<std::string> remaps{};
    auto remaps_array = doc_it->value.GetArray();
    remaps.reserve(remaps_array.Size());
    for (rapidjson::SizeType i = 0; i < remaps_array.Size(); ++i)
        remaps.emplace_back(remaps_array[i].GetString());
    return remaps;
}


void write_to_json(const std::string &json_file_name, int pid, std::vector<Keymap> &keylayouts)
{
        Document document;
        Document::AllocatorType &allocator = document.GetAllocator();
        Value root(kObjectType);
        Value key(kStringType);
        Value value(kStringType);
        // current process id
        key.SetString("pid", allocator);
        root.AddMember(key, pid, allocator);
        key.SetString("count_of_keyboard_layouts", allocator);
        root.AddMember(key, keylayouts.size(), allocator);
        Value extrachild(kObjectType);
        size_t index = 1;
        for(auto &layout: keylayouts){
            Value prechild(kObjectType);
            {
                Value child(kObjectType);
                for (auto &key_from_keys:layout.changed_vector_of_buttons) {
                    Value array(rapidjson::kArrayType);
                    key.SetString(key_from_keys.first.c_str(), allocator);
                    for (auto & it : key_from_keys.second) {
                        value.SetString(it.c_str(), it.length(), allocator);
                        array.PushBack(value, allocator);
                    }
                    child.AddMember(key, array, allocator);
                }
                key.SetString("keymap", allocator);
                prechild.AddMember(key, child, allocator);
            }
            {
                Value child(kObjectType);
                key.SetString("type", allocator);
                value.SetString(layout.mode.toStdString().c_str(), allocator);
                child.AddMember(key, value, allocator);
                key.SetString("value", allocator);
                child.AddMember(key, layout.conf_value, allocator);
                key.SetString("mode", allocator);
                prechild.AddMember(key, child, allocator);
            }
            key.SetString(("keymap" + std::to_string(index)).c_str(), allocator);
            extrachild.AddMember(key, prechild, allocator);
        }
        key.SetString("keylayouts", allocator);
        root.AddMember(key, extrachild, allocator);
        StringBuffer buffer;
        PrettyWriter<StringBuffer> writer(buffer);
        root.Accept(writer);

        std::ofstream file{json_file_name};
        file << buffer.GetString();
        file.close();
}

void read_to_json(const std::string &json_file_name, int &pid, std::vector<Keymap> &keylayoutss)
{
    std::ifstream ifs(json_file_name);
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw);
    pid = d["pid"].GetInt();
    size_t count_of_keyboard_layouts = d["count_of_keyboard_layouts"].GetUint64();
    keylayoutss.clear();
    keylayoutss.reserve(count_of_keyboard_layouts);
    for(size_t i = 0; i < count_of_keyboard_layouts; ++i){
        keylayoutss.at(i).mode = d["mode"].GetObject()["type"].GetString();
        keylayoutss.at(i).conf_value = d["conf_value"].GetDouble();
        size_t index = 0;
        for(auto doc_it = d["keylayouts"].MemberBegin(); doc_it != d["keylayouts"].MemberEnd(); ++doc_it){
            for (auto doc_it = d[("keymap" + std::to_string(index)).c_str()].MemberBegin(); doc_it != d[("keymap" + std::to_string(index)).c_str()].MemberEnd(); ++doc_it){
                 keylayoutss.at(index).changed_vector_of_buttons[doc_it->name.GetString()] = array2vector(doc_it);
            }
        }
    }
}
