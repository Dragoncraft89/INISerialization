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
