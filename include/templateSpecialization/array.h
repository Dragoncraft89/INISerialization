
template<typename T, std::size_t Num>
static bool deserializeArray(INISerializer *obj, const std::string &s, std::array<T, Num>* array) {
    if(s.length() < 2 || s.front() != '{' || s.back() != '}') {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for std::array<" + getName<T>()() + "," + std::to_string(Num) + ">: '" + s + "'");
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
