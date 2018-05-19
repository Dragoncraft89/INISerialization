//
// Created by florian on 16.01.18.
//

#include <vector>
#include <type_traits>
#include <functional>

#include <iostream>
#include <fstream>
#include <string>

#include <INISerializer.h>

void INISerializer::INISerializer::errorHandler(int type, std::string s) {
    switch(errorPolicy) {
        case Policies::ISSUE_WARNING: std::cout << "[INISerializer Warning]" << s << std::endl; break;
        case Policies::THROW_ERROR:  throw std::runtime_error(s); break;

        case Policies::CUSTOM_ERROR_HANDLER: if(callback) callback(type, s); break;
    }
}

/* Ini file parser and loads via sections map + deserialization templates */
void INISerializer::INISerializer::loadFromFile(std::string filename) {
    std::ifstream file(filename, std::ios::in);
    if(!file.is_open())
        INISerializer::saveToFile(filename);

    constexpr bool LEFT = false; // Left side of section entry
    constexpr bool RIGHT = true;

    std::vector<std::tuple<std::string, std::string, std::string>> elements; // {section, key, value}

    int line = 1;

    bool escaped = false;
    bool skip = false; // comments
    bool sec = false; // Are we in a section header?
    bool secEnd = false; // Have we completed a section header in the same line?
    bool side = LEFT;

    std::string section;
    std::string name;
    std::string value;

    bool quotes = false;

    char c;
    while(file >> std::noskipws >> c) {
        switch(c) {
            case '"':
                quotes = !quotes;
                goto DEFAULT_CASE;
            case '\t':
            case '\r':
            case ' ':
                if(quotes)
                    goto DEFAULT_CASE;
                break; // ignore chars
            case '[':
                if(escaped)
                    goto DEFAULT_CASE;

                if(skip)
                    break;

                if(sec)
                    errorHandler(ErrorCodes::MALFORMED_INI, "Found '[' in section identifier, you need to escape it with '\\['");
                sec = true;
                section = "";
                break;
            case ']':
                if(escaped)
                    goto DEFAULT_CASE;

                if(skip)
                    break;

                if(!sec)
                    errorHandler(ErrorCodes::MALFORMED_INI, "Found ']' without section, you need to escape it with '\\]'");
                sec = false;
                secEnd = true;
                break;
            case ';':
                if(escaped)
                    goto DEFAULT_CASE;
                skip = true;
                break;
            case '\n':
                if(escaped) {
                    escaped = false;
                    continue;
                }

                if(name != "" && side == LEFT)
                    errorHandler(ErrorCodes::MALFORMED_INI, "Found key without value: '" + name + "'");

                ++line;
                skip = false;
                secEnd = false;
                side = LEFT;

                if(!sec && name != "" && value != "") {
                    elements.push_back({section, name, value});
                    name = "";
                    value = "";
                }
                break;

            case '=':
                if(skip)
                    break;

                if(!sec) {
                    side = !side;
                    break;
                }
                goto DEFAULT_CASE;
            case '\\':
                if(escaped)
                    goto DEFAULT_CASE;
                escaped = true;
                break;
            case 'a':
                if(escaped)
                    c = '\a';
                goto DEFAULT_CASE;
            case 'b':
                if(escaped)
                    c = '\b';
                goto DEFAULT_CASE;
            case 't':
                if(escaped)
                    c = '\t';
                goto DEFAULT_CASE;
            case 'r':
                if(escaped)
                    c = '\r';
                goto DEFAULT_CASE;
            case 'n':
                if(escaped)
                    c = '\n';
                goto DEFAULT_CASE;
            default:
                DEFAULT_CASE:
                if(skip)
                    break;

                escaped = false;
                if(secEnd)
                    errorHandler(ErrorCodes::MALFORMED_INI, "Key on the same line as section");

                if(sec)
                    section += c;
                else
                    (side == LEFT?name:value) += c;
        }
    }

    if(sec)
        errorHandler(ErrorCodes::MALFORMED_INI, "Section tag still open on EOF");

    if(name != "" && side == LEFT)
        errorHandler(ErrorCodes::MALFORMED_INI, "Found key without value: '" + name + "'");

    if(!sec && name != "" && value != "")
        elements.push_back({section, name, value});

    for(std::tuple<std::string, std::string, std::string> &e:elements) {
        auto it = sections.find(std::get<0>(e));
        if(it != sections.end()) {
            auto sectionEntry = it->second.find(std::get<1>(e));
            if(sectionEntry != it->second.end()) {
                std::function<void(INISerializer *, std::string, void*)> deserialize = std::get<1>(sectionEntry->second);
                deserialize(this, std::get<2>(e), std::get<2>(sectionEntry->second));
            } else {
                errorHandler(ErrorCodes::MALFORMED_INI, "Unknown key: " + std::get<0>(e) + "::" + std::get<1>(e));
            }
        } else {
            errorHandler(ErrorCodes::MALFORMED_INI, "Unknown section: " + std::get<0>(e));
        }
    }
}

/* Writes ini files via serialization templates */
void INISerializer::INISerializer::saveToFile(std::string filename) {
    std::ofstream file(filename, std::ios::out | std::ios::trunc);

    for(std::pair<const std::string, sectionEntry> &s: sections) {
        std::string section = s.first;
        file << '[' << section << ']' << '\n';
        for(std::pair<const std::string, serializationFunctionLookup> &entry:s.second) {
            std::string name = entry.first;

            std::function<std::string(INISerializer*, void*)> serialize = std::get<0>(entry.second);
            std::string value = serialize(this, std::get<2>(entry.second));

            file << name << '=' << value << '\n';
        }
    }
}
