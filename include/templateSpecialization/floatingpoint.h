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

template<>
bool deserialize<long double>(INISerializer *obj, const std::string &s, long double *ptr) {
    char *c;
    long double num = strtold(s.data(), &c);
    if(!*c) {
        *ptr = num;
        return true;
    } else {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for long double: '" + s + "'");
        return false;
    }
}

template<>
std::string serialize<long double>(INISerializer *obj, const long double *ptr) {
    return std::to_string(*ptr);
}
