
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
