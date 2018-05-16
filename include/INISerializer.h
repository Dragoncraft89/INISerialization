//
// Created by florian on 14.01.18.
//

#ifndef OPENGL_OPTIONS_H
#define OPENGL_OPTIONS_H

#include <utility>
#include <functional>
#include <string>
#include <map>

namespace INISerializer {
    namespace ErrorCodes {
        static constexpr int MALFORMED_INI = 0;
        static constexpr int INVALID_VALUE = 1;
    }

    namespace Policies {
        static constexpr int THROW_ERROR = 0;
        static constexpr int ISSUE_WARNING = 1;
        static constexpr int CUSTOM_ERROR_HANDLER = 2;
    }

    class INISerializer {
    private:
        typedef std::function<std::string(INISerializer*, const void*)> serializationFunctionType;
        typedef std::function<void(INISerializer*, const std::string&, void*)> deserializationFunctionType;

        typedef std::tuple<serializationFunctionType, deserializationFunctionType, void*> serializationFunctionLookup;

        typedef std::map<std::string, serializationFunctionLookup> sectionEntry;

        static std::map<std::string, sectionEntry> sections;

        int errorPolicy = Policies::THROW_ERROR;
        std::function<void(int, std::string)> callback;
    public:
        template<typename T>
        void registerVariable(std::string section, std::string key, T &value) {
            auto iterator = sections.find(section);
            if(iterator != sections.end()) {
                iterator->second.insert({key, makeEntry(value)});
            } else {
                sections.insert({section, {key, makeEntry(value)}});
            }
        }

        void errorHandler(int type, std::string s);

        void loadFromFile(std::string filename);
        void saveToFile(std::string filename);
    };
}

#include <Serialization.h>
#endif //OPENGL_OPTIONS_H
