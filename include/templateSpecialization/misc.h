
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
bool deserialize<std::string>(INISerializer *obj, const std::string &s, std::string *ptr) {
    *ptr = s;
}

template<>
std::string serialize<std::string>(INISerializer *obj, const std::string *ptr) {
    return *ptr;
}
