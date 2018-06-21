
template<typename A, typename B>
static bool deserializePair(INISerializer *obj, const std::string &s, std::pair<A, B> *ptr) {
    if(s.length() < 2 || s.front() != '{' || s.back() != '}') {
        obj->errorHandler(ErrorCodes::INVALID_VALUE, "Invalid value for std::pair<" + std::string(typeid(A).name()) + ", " + std::string(typeid(B).name()) + ">: '" + s + "'");
        return false;
    }

    std::size_t start = 1;
    std::size_t middle = findDelimiterPos(obj, s, start, s.length()-1);
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
