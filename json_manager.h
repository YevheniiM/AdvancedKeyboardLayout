#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

#include <map>
#include <vector>
#include <fstream>
#include <fstream>
#include <algorithm>

#include "keymap.h"
#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/istreamwrapper.h"

std::vector<std::string> array2vector(const rapidjson::Document::ConstMemberIterator &doc_it);

void read_to_json(const std::string &json_file_name, int &pid, std::vector<Keymap> &keylayoutss);

void write_to_json(const std::string &json_file_name, int id, std::vector<Keymap> &keylayoutss);

#endif // JSON_MANAGER_H
