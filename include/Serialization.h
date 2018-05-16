
namespace INISerializer {
namespace SerializationFunctions {

template<typename T>
static std::tuple<std::function<std::string(const void*)>, std::function<void(const std::string&, void*)>, void*> makeEntry(T &t);

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

template<typename... Args>
static bool deserializeArray(INISerializer *obj, const std::string &s, std::array<Args...>* tuple);

template<typename... Args>
static std::string serializeArray(INISerializer *obj, const std::array<Args...>* tuple);

/* default serialization / deserialization template, delegate to special functions or raise a compile error */
template<typename T>
static bool deserialize(INISerializer *obj, const std::string &s, T* ptr) {
    if constexpr(is_specialization_of<std::tuple, T>::value)
        deserializeTuple(obj, s, ptr);
    else if constexpr(is_specialization_of<std::pair, T>::value)
        deserializePair(obj, s, ptr);
    else if constexpr(is_array<T>::value)
        deserializeArray(obj, s, ptr);
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

/* template specialization serialization/deserialization */
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
bool deserialize<std::string>(INISerializer *obj, const std::string &s, std::string *ptr) {
    *ptr = s;
}

template<>
std::string serialize<std::string>(INISerializer *obj, const std::string *ptr) {
    return *ptr;
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
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for double: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<double>(INISerializer *obj, const double *ptr) {
    return std::to_string(*ptr);
}

template<typename A, typename B>
static bool deserializePair(INISerializer *obj, const std::string &s, std::pair<A, B> *ptr) {
    if(s.length() < 2 || s.front() != '{' || s.back() != '}') {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for std::pair<" + std::string(typeid(A).name()) + ", " + std::string(typeid(B).name()) + ">: '" + s + "'");
        return false;
    }

    int start = 1;
    int middle = s.find_first_of(",");
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

    if(s.find_first_of(',', middle+1) != std::string::npos) {
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

template<typename T>
constexpr std::string getName() {
    return typeid(T).name();
}

template<typename T, typename... Args>
constexpr std::string getName() {
    return std::string(typeid(T).name()) + ", " + getName<Args...>();
}

template<typename... Args>
static bool deserializeTuple(INISerializer *obj, const std::string &s, std::tuple<Args...>* tuple) {
    if(s.length() < 2 || s.front() != '{' || s.back() != '}') {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for std::tuple<" + getName<Args...>() + ">: '" + s + "'");
    }

    constexpr int len = std::tuple_size<std::tuple<Args...>>::value;

    std::tuple<Args...> result;

    int last = 1;
    int current;

    int count = 0;
    while((current = s.find_first_of(',', last)) != std::string::npos) {
        if(count == len) {
            obj->errorHandler(ErrorCodes::INVALID_VALUE, "Too many values for std::tuple<" + getName<Args...>() + ">: '" + s + "'");
            return false;
        }

        try {
            if(!deserialize(obj, s.substr(last, current - last), &std::get<count>(result))) {
                obj->errorHandler(ErrorCodes::INVALID_VALUE, "While deserializing std::tuple<" + getName<Args...>() + ">: '" + s + "'");
                return false;
            }
        } catch(std::runtime_error &e) {
            obj->errorHandler(ErrorCodes::INVALID_VALUE, std::string(e.what()) + "\nWhile deserializing std::tuple<" + getName<Args...>() + ">: '" + s + "'");
        }

        last = current+1;
        ++count;
    }

    if(count < len) {
        try {
            if(!deserialize(obj, s.substr(last, s.length()-1 - last), &std::get<count>(result))) {
                obj->errorHandler(ErrorCodes::INVALID_VALUE, "While deserializing std::tuple<" + getName<Args...>() + ">: '" + s + "'");
                return false;
            }
        } catch(std::runtime_error &e) {
            obj->errorHandler(ErrorCodes::INVALID_VALUE, std::string(e.what()) + "\nWhile deserializing std::tuple<" + getName<Args...>() + ">: '" + s + "'");
        }

        ++count;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Too many values for std::tuple<" + getName<Args...>() + ">: '" + s + "'");
        return false;
    }

    if(count != len) {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Too few values for std::tuple<" + getName<Args...>() + ">: '" + s + "'");
        return false;
    }

    *tuple = result;
}

template<typename... Args>
static std::string serializeTuple(INISerializer *obj, const std::tuple<Args...>* tuple) {
    constexpr int len = std::tuple_size<std::tuple<Args...>>::value;

    std::string s = "{";
    for(int i = 0; i < len - 1; ++i) {
        s += serialize(obj, std::get<i>(tuple)) + ",";
    }

    s += serialize(obj, std::get<len-1>(tuple)) + "}";

    return s;
}

template<>
std::string serializeTuple<>(INISerializer *obj, const std::tuple<> *tuple) {
    return "{}";
}

template<typename... Args>
static bool deserializeArray(INISerializer *obj, const std::string &s, std::tuple<Args...>* array) {
    if(s.length() < 2 || s.front() != '{' || s.back() != '}') {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for std::tuple<" + getName<Args...>() + ">: '" + s + "'");
    }

    constexpr int len = std::tuple_size<std::array<Args...>>::value;

    std::array<Args...> result = array;

    int last = 1;
    int current;

    int count = 0;
    while((current = s.find_first_of(',', last)) != std::string::npos) {
        if(count == len) {
            obj->errorHandler(ErrorCodes::INVALID_VALUE, "Too many values for std::array<" + getName<Args...>() + ">: '" + s + "'");
            return false;
        }

        try {
            if(!deserialize(obj, s.substr(last, current-last), &std::get<count>(result))) {
                obj->errorHandler(ErrorCodes::INVALID_VALUE, "While deserializing std::array<" + getName<Args...>() + ">: '" + s + "'");
                return false;
            }
        } catch(std::runtime_error &e) {
            obj->errorHandler(ErrorCodes::INVALID_VALUE, std::string(e.what()) + "\nWhile deserializing std::array<" + getName<Args...>() + ">: '" + s + "'");
        }

        last = current+1;
        ++count;
    }

    if(count < len) {
        try {
            if(!deserialize(obj, s.substr(last, s.length()-1-last), &std::get<count>(result))) {
                obj->errorHandler(ErrorCodes::INVALID_VALUE, "While deserializing std::array<" + getName<Args...>() + ">: '" + s + "'");
                return false;
            }
        } catch(std::runtime_error &e) {
            obj->errorHandler(ErrorCodes::INVALID_VALUE, std::string(e.what()) + "\nWhile deserializing std::array<" + getName<Args...>() + ">: '" + s + "'");
        }
        ++count;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Too many values for std::array<" + getName<Args...>() + ">: '" + s + "'");
        return false;
    }

    if(count != len) {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Too few values for std::array<" + getName<Args...>() + ">: '" + s + "'");
        return false;
    }

    *array = result;
}

template<typename... Args>
static std::string serializeArray(INISerializer *obj, const std::array<Args...>* array) {
    constexpr int len = std::tuple_size<std::array<Args...>>::value;

    std::string s = "{";
    for(int i = 0; i < len - 1; ++i) {
        s += serialize(obj, std::get<i>(array)) + ",";
    }

    if(len != 0)
        s += serialize(obj, std::get<len-1>(array));

    s += "}";

    return s;
}

template<typename T>
static void deserializeHelper(INISerializer *obj, const std::string &s, void* ptr) {
    deserialize<T>(obj, s, static_cast<T*>(ptr));
}

template<typename T>
static std::string serializeHelper(INISerializer *obj, const void* ptr) {
    return serialize<T>(obj, static_cast<const T*>(ptr));
}

template<typename T>
static std::tuple<std::function<std::string(INISerializer *obj, const void*)>, std::function<void(INISerializer *obj, const std::string&, void*)>, void*> makeEntry(T &t) {
    return {serializeHelper<T>, deserializeHelper<T>, static_cast<void*>(&t)};
}

}
}
