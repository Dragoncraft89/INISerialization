
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
inline bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

inline std::string replaceAll(std::string str, const std::string &from, const std::string &to) {
    if(from.empty())
        return str;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }

    return str;
}

template<>
bool deserialize<std::string>(INISerializer *obj, const std::string &s, std::string *ptr) {
    if(s.length() >= 2 && ((s.front() == '"' && s.back() == '"') || (s.front() == '\'' && s.back() == '\''))) {
        *ptr = replaceAll(replaceAll(s.substr(1, s.length()-2), "\\\"", "\""), "\\'", "'");
    } else {
        *ptr = s;
    }

    return true;
}

template<>
std::string serialize<std::string>(INISerializer *obj, const std::string *ptr) {
    for(std::size_t i = 0; i < ptr->length(); ++i) {
        if(std::isspace((*ptr)[i]))
            return "\"" + (*ptr) + "\"";
    }
    return *ptr;
}
