
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

template<typename T, typename... Args>
struct getName {
    std::string operator()() {
        return getName<T>()() + ", " + getName<Args...>()();
    }
};

template<typename T>
struct getName<T> {
    std::string operator()() {
        return typeid(T).name();
    }
};

template<>
struct getName<char> {
    std::string operator()() {
        return "char";
    }
};

template<>
struct getName<short> {
    std::string operator()() {
        return "short";
    }
};

template<>
struct getName<int> {
    std::string operator()() {
        return "int";
    }
};

template<>
struct getName<long> {
    std::string operator()() {
        return "long";
    }
};

template<>
struct getName<long long> {
    std::string operator()() {
        return "long long";
    }
};

template<>
struct getName<unsigned char> {
    std::string operator()() {
        return "unsigned char";
    }
};

template<>
struct getName<unsigned short> {
    std::string operator()() {
        return "short";
    }
};

template<>
struct getName<unsigned int> {
    std::string operator()() {
        return "int";
    }
};

template<>
struct getName<unsigned long> {
    std::string operator()() {
        return "long";
    }
};

template<>
struct getName<unsigned long long> {
    std::string operator()() {
        return "long long";
    }
};

template<>
struct getName<float> {
    std::string operator()() {
        return "float";
    }
};

template<>
struct getName<double> {
    std::string operator()() {
        return "double";
    }
};

template<>
struct getName<long double> {
    std::string operator()() {
        return "long double";
    }
};

template<>
struct getName<std::string> {
    std::string operator()() {
        return "std::string";
    }
};

template<>
struct getName<bool> {
    std::string operator()() {
        return "bool";
    }
};

template<typename... Args>
struct getName<std::tuple<Args...>> {
    std::string operator()() {
        return "std::tuple<" + getName<Args...>()() + ">";
    }
};

template<typename T, std::size_t Num>
struct getName<std::array<T, Num>> {
    std::string operator()() {
        return "std::array<" + getName<T>()() + ", " + std::to_string(Num) + ">";
    }
};

template<typename A, typename B>
struct getName<std::pair<A, B>> {
    std::string operator()() {
        return "std::pair<" + getName<A>()() + ", " + getName<B>()() + ">";
    }
};
