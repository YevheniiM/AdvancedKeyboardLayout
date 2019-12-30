#include "json_manager.h"

using rapidjson::Value;
using rapidjson::Writer;
using rapidjson::Document;
using rapidjson::kObjectType;
using rapidjson::kStringType;
using rapidjson::StringBuffer;
using rapidjson::IStreamWrapper;

#include <iostream>

void write_to_json(const std::string &json_file_name, int pid, std::string mode, double conf_value, std::map<std::string, std::vector<std::string> > keys)
{
        Document document;
        Document::AllocatorType &allocator = document.GetAllocator();
        Value root(kObjectType);
        Value key(kStringType);
        Value value(kStringType);
        // current process id
        key.SetString("pid", allocator);
        root.AddMember(key, pid, allocator);
        {
            Value child(kObjectType);
            for (auto &key_from_keys:keys) {
                Value array(rapidjson::kArrayType);
                key.SetString(key_from_keys.first.c_str(), allocator);
                for (auto & it : key_from_keys.second) {
                    value.SetString(it.c_str(), it.length(), allocator);
                    array.PushBack(value, allocator);
                }
                child.AddMember(key, array, allocator);
            }
            key.SetString("keymap", allocator);
            root.AddMember(key, child, allocator);
        }
        {
            Value child(kObjectType);
            key.SetString("type", allocator);
            value.SetString(mode.c_str(), allocator);
            child.AddMember(key, value, allocator);
            key.SetString("value", allocator);
            child.AddMember(key, conf_value, allocator);
            key.SetString("mode", allocator);
            root.AddMember(key, child, allocator);
        }
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        root.Accept(writer);

        std::ofstream file{json_file_name};
        file << buffer.GetString();
        file.close();
}

RemapperConf confs_from_json(const std::string &json_file_name)
{
    std::ifstream ifs(json_file_name);
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw);
    return {d};
}
