#include <string>
#ifndef _WIN32
#include <csignal>
#include <csetjmp>
#include <string.h>
#endif

#include <iostream>
#include <stdexcept>
#include <vector>
#include <chrono>
#include <thread>
#include <functional>

#ifndef UNIT_TESTPLUSPLUS_H
#define UNIT_TESTPLUSPLUS_H
template<bool f()>
bool test();

template <template<typename...> typename, typename> struct is_specialization_of: std::false_type {};
template <template<typename...> typename A, template<typename...> typename B, typename ...T>
struct is_specialization_of<A, B<T...>>: std::is_same<A<T...>, B<T...>> {};

/** Checks if a type is a specialization of std::array<type, num> because is_specialization_of doesn't work */
template <typename>
struct is_array: std::false_type {};

template <typename T, std::size_t Num>
struct is_array<std::array<T, Num>>: std::true_type {};

template <typename>
struct is_vector: std::false_type {};

template <typename T>
struct is_vector<std::vector<T>>: std::true_type {};

template<typename> struct isStringLiteral: std::false_type {};
template<std::size_t len> struct isStringLiteral<char[len]>: std::true_type {};
template<std::size_t len> struct isStringLiteral<const char[len]>: std::true_type {};

template<typename... Args>
inline std::string tuple_as_string(std::tuple<Args...> &tuple);
template<typename T, std::size_t Num>
inline std::string array_as_string(std::array<T, Num> &array);
template<typename T>
inline std::string vector_as_string(std::vector<T> &vector);

template<typename T>
inline std::string as_string(T &t) {
    if constexpr(is_specialization_of<std::tuple, T>::value) {
        return "{" + tuple_as_string(t) + "}";
    } else if constexpr(is_specialization_of<std::pair, T>::value) {
        return "{" + as_string(std::get<0>(t)) + "," + as_string(std::get<1>(t)) + "}";
    } else if constexpr(is_array<T>::value) {
        return "{" + array_as_string(t) + "}";
    } else if constexpr(isStringLiteral<T>::value) {
        const char *c = t;
        return as_string<const char*>(c);
    } else if constexpr(is_vector<T>::value) {
        return "{" + vector_as_string(t) + "}";
    } else {
        return std::to_string(t);
    }
}

template<>
inline std::string as_string<std::string>(std::string &s) {
    return "\"" + s + "\"";
}

template<>
inline std::string as_string<const std::string>(const std::string &s) {
    return "\"" + s + "\"";
}

template<>
inline std::string as_string<char *>(char * &c) {
    return "\"" + std::string(c) + "\"";
}

template<>
inline std::string as_string<const char*>(const char *&c) {
    return "\"" + std::string(c) + "\"";
}

template<std::size_t I = 0, std::size_t len, typename... Tp>
inline std::enable_if_t<I == len-1, std::string>
tuple_as_string_helper(std::tuple<Tp...>& t)
{
      return as_string(std::get<I>(t));
}

template<std::size_t I = 0, std::size_t len, typename... Tp>
inline std::enable_if_t<I < len-1, std::string>
tuple_as_string_helper(std::tuple<Tp...>& t)
{
    return as_string(std::get<I>(t)) + "," + tuple_as_string_helper<I + 1, len, Tp...>(t);
}

template<typename... Args>
inline std::string tuple_as_string(std::tuple<Args...> &tuple) {
    constexpr size_t len = std::tuple_size<std::tuple<Args...>>::value;

    std::string s = "{" + tuple_as_string_helper<0, len, Args...>(tuple) + "}";

    return s;
}

template<>
inline std::string tuple_as_string<>(std::tuple<> &tuple) {
    return "{}";
}

template<typename T, std::size_t Num>
inline std::string array_as_string(std::array<T, Num> &array) {
    constexpr int len = std::tuple_size<std::array<T, Num>>::value;

    std::string s;
    for(int i = 0; i < len - 1; ++i) {
        T value = array[i];
        s += as_string<T>(value) + ",";
    }

    if(len != 0) {
        T value = array[len-1];
        s += as_string<T>(value);
    }

    return s;
}

template<typename T>
inline std::string vector_as_string(std::vector<T> &vector) {
    int len = vector.size();

    std::string s;
    for(int i = 0; i < len - 1; ++i) {
        T value = vector[i];
        s += as_string<T>(value) + ",";
    }

    if(len != 0) {
        T value = vector[len-1];
        s += as_string<T>(value);
    }

    return s;
}

#define ASSERT_EQU(x, y, msg) { auto tmp_x = x; auto tmp_y = y; if(tmp_x != tmp_y) throw std::runtime_error(as_string(tmp_x) + " != " + as_string(tmp_y) + " (" + __func__ + " on line: " + std::to_string(__LINE__) + "), message: " + as_string(msg)); }
#define ASSERT_TRUE(x, msg) { auto tmp_x = x; if(!tmp_x) throw std::runtime_error("Expected true, got: " + as_string(tmp_x) + " (" + __func__ + " on line: " + std::to_string(__LINE__) + "), message: " + as_string(msg)); }
#define ASSERT_FALSE(x, msg) { auto tmp_x = x; if(tmp_x) throw std::runtime_error("Expected false, got: " + as_string(tmp_x) + " (" + __func__ + " on line: " + std::to_string(__LINE__) + "), message: " + as_string(msg)); }
#define ERROR(msg) {std::cerr << msg << std::endl; }
#define TEST(name) bool name(); \
    template<> inline std::string getName<name>() { return #name; } \
    StaticInitHelper __init_##name##__(test<name>); \
    bool name()

template<bool ()>
inline std::string getName();

static std::vector<std::string> failedTests;
static jmp_buf gBuffer;
template<bool f()>
inline bool test() {
    std::string name = getName<f>();
    std::cout << "Testing \'" << name << "\'" << std::endl;
    try {
        int sig;
        if((sig = setjmp(gBuffer)) == 0) {
            bool succ = f();

            if(succ) {
                std::cout << "\033[1;32mTest \'" << name << "\' executed succesfully\033[m\n" << std::endl;
            } else {
                std::cerr << "Test \'" << name << "\' failed\n" << std::endl;
                failedTests.push_back(name);
            }

            return succ;
        } else {
            throw sig;
        }
    } catch(const std::runtime_error &e) {
        std::cerr << "Test \'" << name << "\' failed with exception\n" << e.what() << '\n' << std::endl;
    } catch(const int &sig) {
        std::cerr << "Test \'" << name << "\' failed with signal " << sig << '\n' << std::endl;
    } catch(...) {
        std::cerr << "Test \'" << name << "\' failed with unknown reason\n" << std::endl;
    }

    return false;
}

inline std::vector<std::function<bool()>> &getTests() {
    static std::vector<std::function<bool()>> testFunctions;
    return testFunctions;
}

class StaticInitHelper {
public:
    StaticInitHelper(bool f()) {
        getTests().push_back(f);
    }
};
#endif
