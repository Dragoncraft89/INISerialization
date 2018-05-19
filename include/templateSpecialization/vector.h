
template<typename T>
static bool deserializeVector(INISerializer *obj, const std::string &s, std::vector<T>* vector) {
    if(s.length() < 2 || s.front() != '{' || s.back() != '}') {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for std::vector<" + getName<T>()() + ">: '" + s + "'");
    }

    std::vector<T> result = *vector;

    int last = 1;
    int current;

    while((current = findDelimiterPos(obj, s, last, s.length()-1)) != std::string::npos) {
        try {
            T value;
            if(!deserialize(obj, s.substr(last, current-last), &value)) {
                obj->errorHandler(ErrorCodes::INVALID_VALUE, "While deserializing std::vector<" + getName<T>()() + ">: '" + s + "'");
                return false;
            }
            result.push_back(value);
        } catch(std::runtime_error &e) {
            obj->errorHandler(ErrorCodes::INVALID_VALUE, std::string(e.what()) + "\nWhile deserializing std::vector<" + getName<T>()() + ">: '" + s + "'");
        }

        last = current+1;
    }

    try {
        T value;
        if(!deserialize(obj, s.substr(last, s.length()-1-last), &value)) {
            obj->errorHandler(ErrorCodes::INVALID_VALUE, "While deserializing std::vector<" + getName<T>()() + ">: '" + s + "'");
            return false;
        }
        result.push_back(value);
    } catch(std::runtime_error &e) {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, std::string(e.what()) + "\nWhile deserializing std::vector<" + getName<T>()() + ">: '" + s + "'");
    }

    *vector = result;
    return true;
}

template<typename T>
static std::string serializeVector(INISerializer *obj, const std::vector<T> *vector) {
    int len = vector->size();

    std::string s = "{";
    for(int i = 0; i < len - 1; ++i) {
        T value = (*vector)[i];
        s += serialize<T>(obj, &value) + ",";
    }

    if(len != 0) {
        T value = (*vector)[len-1];
        s += serialize<T>(obj, &value);
    }

    s += "}";

    return s;
}
