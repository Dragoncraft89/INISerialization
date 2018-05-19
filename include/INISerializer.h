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

    class INISerializer;

    namespace SerializationFunctions {
    /* Beware, template magic */
    /** Checks if B<T> is a specialization of A, e.g. B = A */
    template <template<typename...> typename, typename> struct is_specialization_of: std::false_type {};
    template <template<typename...> typename A, template<typename...> typename B, typename ...T>
    struct is_specialization_of<A, B<T...>>: std::is_same<A<T...>, B<T...>> {};

    /** Checks if a type is a specialization of std::array<type, num> because is_specialization_of doesn't work */
    template <typename>
    struct is_array: std::false_type {};

    template <typename T, std::size_t Num>
    struct is_array<std::array<T, Num>>: std::true_type {};

    /** Compile time error assertion */
    template<bool b, typename T>
    struct assertMissingSpecialization{
        /** Need to wrap it in a struct, or else the compiler aborts everytime he finds a static_assert(false) that is reachable,
         * especially bad in template specialization, because it will always complain even if the template isn't instantiated */
        static_assert(b, "Missing template");
    };

    /* forward declarations */
    template<typename A, typename B>
    static bool deserializePair(INISerializer *obj, const std::string &s, std::pair<A, B> *ptr);

    template<typename A, typename B>
    static std::string serializePair(INISerializer *obj, const std::pair<A, B> *p);

    template<typename... Args>
    static bool deserializeTuple(INISerializer *obj, const std::string &s, std::tuple<Args...>* tuple);

    template<typename... Args>
    static std::string serializeTuple(INISerializer *obj, const std::tuple<Args...>* tuple);

    template<typename T, std::size_t Num>
    static bool deserializeArray(INISerializer *obj, const std::string &s, std::array<T, Num>* tuple);

    template<typename T, std::size_t Num>
    static std::string serializeArray(INISerializer *obj, const std::array<T, Num>* tuple);
    /* default serialization / deserialization template, delegate to special functions or raise a compile error */
    template<typename T>
    static bool deserialize(INISerializer *obj, const std::string &s, T* ptr) {
        if constexpr(is_specialization_of<std::tuple, T>::value)
            return deserializeTuple(obj, s, ptr);
        else if constexpr(is_specialization_of<std::pair, T>::value)
            return deserializePair(obj, s, ptr);
        else if constexpr(is_array<T>::value)
            return deserializeArray(obj, s, ptr);
        else
          assertMissingSpecialization<false, T>(); // compile time error for missing specialization
    }

    template<typename T>
    static std::string serialize(INISerializer *obj, const T* ptr) {
        if constexpr(is_specialization_of<std::tuple, T>::value)
            return serializeTuple(obj, ptr);
        else if constexpr(is_specialization_of<std::pair, T>::value)
            return serializePair(obj, ptr);
        else if constexpr(is_array<T>::value)
            return serializeArray(obj, ptr);
        else
            assertMissingSpecialization<false, T>(); // compile time error for missing specialization
    }
    template<typename T>
    void deserializeHelper(INISerializer *obj, const std::string &s, void* ptr) {
        deserialize<T>(obj, s, static_cast<T*>(ptr));
    }

    template<typename T>
    std::string serializeHelper(INISerializer *obj, const void* ptr) {
        return serialize<T>(obj, static_cast<const T*>(ptr));
    }

    template<typename T>
    static std::tuple<std::function<std::string(INISerializer *obj, const void*)>, std::function<void(INISerializer *obj, const std::string&, void*)>, void*> makeEntry(T &t) {
        return {serializeHelper<T>, deserializeHelper<T>, static_cast<void*>(&t)};
    }
    }

    class INISerializer {
    private:
        typedef std::function<std::string(INISerializer*, const void*)> serializationFunctionType;
        typedef std::function<void(INISerializer*, const std::string&, void*)> deserializationFunctionType;

        typedef std::tuple<serializationFunctionType, deserializationFunctionType, void*> serializationFunctionLookup;

        typedef std::map<std::string, serializationFunctionLookup> sectionEntry;

        std::map<std::string, sectionEntry> sections;

        int errorPolicy = Policies::THROW_ERROR;
        std::function<void(int, std::string)> callback;
    public:
        template<typename T>
        void registerVariable(std::string section, std::string key, T &value) {
            section.erase(std::remove_if(section.begin(), section.end(), ::isspace), section.end()); // white space is not allowed in sections/keys
            key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());

            auto iterator = sections.find(section);
            if(iterator != sections.end()) {
                iterator->second.insert({key, SerializationFunctions::makeEntry(value)});
            } else {
                sections.insert({section, {{key, SerializationFunctions::makeEntry(value)}}});
            }
        }

        void errorHandler(int type, std::string s);

        void loadFromFile(std::string filename);
        void saveToFile(std::string filename);
    };
}

#include <Serialization.h>
#endif //OPENGL_OPTIONS_H
