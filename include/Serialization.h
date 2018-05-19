#include <locale>
#include <variant>
#include <type_traits>

namespace INISerializer {

namespace SerializationFunctions {

/* template specialization serialization/deserialization */
template<>
bool deserialize<char>(INISerializer *obj, const std::string &s, char *ptr) {
    char *p;
    char num = strtol(s.data(), &p, 10);
    if(!*p) { // num is valid
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for char: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<char>(INISerializer *obj, const char *ptr) {
    return std::to_string(*ptr);
}

template<>
bool deserialize<short>(INISerializer *obj, const std::string &s, short *ptr) {
    char *p;
    short num = strtol(s.data(), &p, 10);
    if(!*p) { // num is valid
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for short: '" + s + "'");
        return false;
    }
}

template<>
bool deserialize<int>(INISerializer *obj, const std::string &s, int *ptr) {
    char *p;
    int num = strtol(s.data(), &p, 10);
    if(!*p) { // num is valid
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for int: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<int>(INISerializer *obj, const int *ptr) {
    return std::to_string(*ptr);
}

template<>
std::string serialize<short>(INISerializer *obj, const short *ptr) {
    return std::to_string(*ptr);
}

template<>
bool deserialize<long>(INISerializer *obj, const std::string &s, long *ptr) {
    char *p;
    long num = strtol(s.data(), &p, 10);
    if(!*p) { // num is valid
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for char: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<long>(INISerializer *obj, const long *ptr) {
    return std::to_string(*ptr);
}

template<>
bool deserialize<long long>(INISerializer *obj, const std::string &s, long long *ptr) {
    char *p;
    long long num = strtoll(s.data(), &p, 10);
    if(!*p) { // num is valid
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for char: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<long long>(INISerializer *obj, const long long *ptr) {
    return std::to_string(*ptr);
}

template<>
bool deserialize<unsigned char>(INISerializer *obj, const std::string &s, unsigned char *ptr) {
    char *p;
    unsigned char num = strtoul(s.data(), &p, 10);
    if(!*p) { // num is valid
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for char: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<unsigned char>(INISerializer *obj, const unsigned char *ptr) {
    return std::to_string(*ptr);
}

template<>
bool deserialize<unsigned short>(INISerializer *obj, const std::string &s, unsigned short *ptr) {
    char *p;
    unsigned short num = strtoul(s.data(), &p, 10);
    if(!*p) { // num is valid
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for short: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<unsigned short>(INISerializer *obj, const unsigned short *ptr) {
    return std::to_string(*ptr);
}

template<>
bool deserialize<unsigned int>(INISerializer *obj, const std::string &s, unsigned int *ptr) {
    char *p;
    unsigned int num = strtoul(s.data(), &p, 10);
    if(!*p) { // num is valid
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for unsigned int: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<unsigned int>(INISerializer *obj, const unsigned int *ptr) {
    return std::to_string(*ptr);
}

template<>
bool deserialize<unsigned long>(INISerializer *obj, const std::string &s, unsigned long *ptr) {
    char *p;
    unsigned long num = strtoul(s.data(), &p, 10);
    if(!*p) { // num is valid
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for char: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<unsigned long>(INISerializer *obj, const unsigned long *ptr) {
    return std::to_string(*ptr);
}

template<>
bool deserialize<unsigned long long>(INISerializer *obj, const std::string &s, unsigned long long *ptr) {
    char *p;
    unsigned long long num = strtoll(s.data(), &p, 10);
    if(!*p) { // num is valid
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for char: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<unsigned long long>(INISerializer *obj, const unsigned long long *ptr) {
    return std::to_string(*ptr);
}

template<>
bool deserialize<std::string>(INISerializer *obj, const std::string &s, std::string *ptr) {
    *ptr = s;
}

template<>
std::string serialize<std::string>(INISerializer *obj, const std::string *ptr) {
    return *ptr;
}

template<>
bool deserialize<bool>(INISerializer *obj, const std::string &s, bool *ptr) {
    if(std::tolower(s, std::locale()) == "true") {
        *ptr = true;
        return true;
    } else if(std::tolower(s, std::locale()) == "false") {
        *ptr = false;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for bool: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<bool>(INISerializer *obj, const bool *ptr) {
    return *ptr?"true":"false";
}

template<>
bool deserialize<float>(INISerializer *obj, const std::string &s, float *ptr) {
    char *c;
    float num = strtof(s.data(), &c);
    if(!*c) {
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for float: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<float>(INISerializer *obj, const float *ptr) {
    return std::to_string(*ptr);
}

template<>
bool deserialize<double>(INISerializer *obj, const std::string &s, double *ptr) {
    char *c;
    double num = strtod(s.data(), &c);
    if(!*c) {
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for float: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<double>(INISerializer *obj, const double *ptr) {
    return std::to_string(*ptr);
}

template<>
bool deserialize<long double>(INISerializer *obj, const std::string &s, long double *ptr) {
    char *c;
    long double num = strtold(s.data(), &c);
    if(!*c) {
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for float: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<long double>(INISerializer *obj, const long double *ptr) {
    return std::to_string(*ptr);
}

inline std::size_t findDelimiterPos(INISerializer *obj, const std::string &s, std::size_t offset, std::size_t end) {
    std::size_t depth = 0;
    for(int i = offset; i < std::min(end, s.length()); ++i) {
        switch(s[i]) {
            case '{':
                ++depth; break;
            case '}':
                if(depth == 0) {
                    obj->errorHandler(ErrorCodes::INVALID_VALUE, "Unexpected token '}'");
                    return std::string::npos;
                }
                --depth;
                break;
            case ',':
                if(depth == 0)
                    return i;
        }
    }

    return std::string::npos;
}

inline std::size_t findDelimiterPos(INISerializer *obj, const std::string &s, std::size_t offset = 0) {
    return findDelimiterPos(obj, s, offset, s.length());
}

template<typename A, typename B>
static bool deserializePair(INISerializer *obj, const std::string &s, std::pair<A, B> *ptr) {
    if(s.length() < 2 || s.front() != '{' || s.back() != '}') {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for std::pair<" + std::string(typeid(A).name()) + ", " + std::string(typeid(B).name()) + ">: '" + s + "'");
        return false;
    }

    int start = 1;
    int middle = findDelimiterPos(obj, s, start, s.length()-1);
    if(middle == std::string::npos) {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Too few values for std::pair<" + std::string(typeid(A).name()) + ", " + std::string(typeid(B).name()) + ">: '" + s + "'");
        return false;
    }

    int end = s.length() - 1;
    A first = ptr->first;
    B second = ptr->second;
    try {
        if(!deserialize<A>(obj, s.substr(start, middle - start), &first)) {
            obj->errorHandler(ErrorCodes::INVALID_VALUE, "While deserializing std::pair<" + std::string(typeid(A).name()) + ", " + std::string(typeid(B).name()) + ">: '" + s + "'");
            return false;
        }
    } catch(std::runtime_error &e) {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, std::string(e.what()) + "\nWhile deserializing std::pair<" + std::string(typeid(A).name()) + ", " + std::string(typeid(B).name()) + ">: '" + s + "'");
    }

    if(findDelimiterPos(obj, s, middle+1, end) != std::string::npos) {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Too many values for std::pair<" + std::string(typeid(A).name()) + ", " + std::string(typeid(B).name()) + ">: '" + s + "'");
        return false;
    }

    try {
        if(!deserialize<B>(obj, s.substr(middle+1, end - (middle+1)), &second)) {
            obj->errorHandler(ErrorCodes::INVALID_VALUE, "While deserializing std::pair<" + std::string(typeid(A).name()) + ", " + std::string(typeid(B).name()) + ">: '" + s + "'");
            return false;
        }
    } catch(std::runtime_error &e) {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, std::string(e.what()) + "\nWhile deserializing std::pair<" + std::string(typeid(A).name()) + ", " + std::string(typeid(B).name()) + ">: '" + s + "'");
    }

    ptr->first = first;
    ptr->second = second;

    return true;
}

template<typename A, typename B>
static std::string serializePair(INISerializer *obj, const std::pair<A, B> *p) {
    return "{" + serialize<A>(obj, &p->first) + "," + serialize<B>(obj, &p->second) + "}";
}

template<typename T, typename... Args>
struct getName {
    constexpr std::string operator()() {
        return std::string(typeid(T).name()) + ", " + getName<Args...>()();
    }
};

template<typename T>
struct getName<T> {
    constexpr std::string operator()() {
        return typeid(T).name();
    }
};

template<std::size_t I = 0, std::size_t len, typename... Args>
inline std::enable_if_t<I == len-1, bool>
tuple_deserialize_helper(INISerializer *obj, const std::string s, std::tuple<Args...>& t) {
    std::size_t pos = findDelimiterPos(obj, s, 1, s.length()-1);
    if(pos != std::string::npos) {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Too many values for std::tuple<" + getName<Args...>()() + ">: '" + s + "'");
        return false;
    }

    return deserialize(obj, s.substr(1, s.length()-2), &std::get<I>(t));
}

template<std::size_t I = 0, std::size_t len, typename... Args>
inline std::enable_if_t<I < len-1, bool>
tuple_deserialize_helper(INISerializer *obj, const std::string s, std::tuple<Args...>& t) {
    std::size_t pos = findDelimiterPos(obj, s, 1, s.length()-1);
    if(pos == std::string::npos) {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Too few values for std::tuple<" + getName<Args...>()() + ">: '" + s + "'");
        return false;
    }

    return deserialize(obj, s.substr(1, pos-1), &std::get<I>(t)) && tuple_deserialize_helper<I + 1, len, Args...>(obj, s.substr(pos), t);
}

template<typename... Args>
static bool deserializeTuple(INISerializer *obj, const std::string &s, std::tuple<Args...>* tuple) {
    if(s.length() < 2 || s.front() != '{' || s.back() != '}') {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for std::tuple<" + getName<Args...>()() + ">: '" + s + "'");
    }

    constexpr int len = std::tuple_size<std::tuple<Args...>>::value;

    std::tuple<Args...> result;

    try {
        tuple_deserialize_helper<0, len, Args...>(obj, s, result);
    } catch(std::runtime_error &e) {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, std::string(e.what()) + "\nWhile deserializing std::tuple<" + getName<Args...>()() + ">: '" + s + "'");
    }

    *tuple = result;
    return true;
}

template<std::size_t I = 0, std::size_t len, typename... Tp>
inline std::enable_if_t<I == len-1, std::string>
tuple_serialize_helper(INISerializer *obj, const std::tuple<Tp...>& t)
{
      return serialize(obj, &std::get<I>(t));
}

template<std::size_t I = 0, std::size_t len, typename... Tp>
inline std::enable_if_t<I < len-1, std::string>
  tuple_serialize_helper(INISerializer *obj, const std::tuple<Tp...>& t)
  {
    return serialize(obj, &std::get<I>(t)) + "," + tuple_serialize_helper<I + 1, len, Tp...>(obj, t);
  }

template<typename... Args>
static std::string serializeTuple(INISerializer *obj, const std::tuple<Args...>* tuple) {
    constexpr size_t len = std::tuple_size<std::tuple<Args...>>::value;

    std::string s = "{" + tuple_serialize_helper<0, len, Args...>(obj, *tuple) + "}";

    return s;
}

template<>
std::string serializeTuple<>(INISerializer *obj, const std::tuple<> *tuple) {
    return "{}";
}

template<typename T, std::size_t Num>
static bool deserializeArray(INISerializer *obj, const std::string &s, std::array<T, Num>* array) {
    if(s.length() < 2 || s.front() != '{' || s.back() != '}') {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for std::tuple<" + getName<T>()() + "," + std::to_string(Num) + ">: '" + s + "'");
    }

    constexpr int len = Num;

    std::array<T, Num> result = *array;

    int last = 1;
    int current;

    int count = 0;
    while((current = findDelimiterPos(obj, s, last, s.length()-1)) != std::string::npos) {
        if(count == len) {
            obj->errorHandler(ErrorCodes::INVALID_VALUE, "Too many values for std::array<" + getName<T>()() + "," + std::to_string(Num) + ">: '" + s + "'");
            return false;
        }

        try {
            if(!deserialize(obj, s.substr(last, current-last), &result[count])) {
                obj->errorHandler(ErrorCodes::INVALID_VALUE, "While deserializing std::array<" + getName<T>()() + "," + std::to_string(Num) + ">: '" + s + "'");
                return false;
            }
        } catch(std::runtime_error &e) {
            obj->errorHandler(ErrorCodes::INVALID_VALUE, std::string(e.what()) + "\nWhile deserializing std::array<" + getName<T>()() + "," + std::to_string(Num) + ">: '" + s + "'");
        }

        last = current+1;
        ++count;
    }

    if(count < len) {
        try {
            if(!deserialize(obj, s.substr(last, s.length()-1-last), &result[count])) {
                obj->errorHandler(ErrorCodes::INVALID_VALUE, "While deserializing std::array<" + getName<T>()() + "," + std::to_string(Num) + ">: '" + s + "'");
                return false;
            }
        } catch(std::runtime_error &e) {
            obj->errorHandler(ErrorCodes::INVALID_VALUE, std::string(e.what()) + "\nWhile deserializing std::array<" + getName<T>()() + "," + std::to_string(Num) + ">: '" + s + "'");
        }
        ++count;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Too many values for std::array<" + getName<T>()() + "," + std::to_string(Num) + ">: '" + s + "'");
        return false;
    }

    if(count != len) {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Too few values for std::array<" + getName<T>()() + "," + std::to_string(Num) + ">: '" + s + "'");
        return false;
    }

    *array = result;
    return true;
}

template<typename T, std::size_t Num>
static std::string serializeArray(INISerializer *obj, const std::array<T, Num> *array) {
    constexpr int len = std::tuple_size<std::array<T, Num>>::value;

    std::string s = "{";
    for(int i = 0; i < len - 1; ++i) {
        T value = (*array)[i];
        s += serialize<T>(obj, &value) + ",";
    }

    if(len != 0) {
        T value = (*array)[len-1];
        s += serialize<T>(obj, &value);
    }

    s += "}";

    return s;
}

}
}
